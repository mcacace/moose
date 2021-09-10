//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "libmesh/utility.h"

#include "MFrontNonAssociativeDruckerPrager.h"

registerMooseObject("TensorMechanicsApp", MFrontNonAssociativeDruckerPrager);

InputParameters
MFrontNonAssociativeDruckerPrager::validParams()
{
  InputParameters params = MFrontStressBase::validParams();
  params.addClassDescription("mfront model - non associative Drucker-Prager (perfect) plasticity.");
  params.addRequiredParam<Real>("young_modulus", "The Young modulus.");
  params.addRequiredParam<Real>("poisson_ratio", "The Poisson ratio.");
  params.addRequiredParam<Real>("cohesion", "The cohesion.");
  params.addRequiredParam<Real>("friction_angle", "The friction angle.");
  params.addRequiredParam<Real>("dilation_angle", "The dilation angle.");
  params.addParam<bool>(
      "convert_to_radians", true, "Whether to convert the friction and dilation angle to radians");
  return params;
}

MFrontNonAssociativeDruckerPrager::MFrontNonAssociativeDruckerPrager(
    const InputParameters & parameters)
  : MFrontStressBase(parameters),
    _young_modulus(getParam<Real>("young_modulus")),
    _poisson_ratio(getParam<Real>("poisson_ratio")),
    _cohesion(getParam<Real>("cohesion")),
    _friction_angle(getParam<Real>("friction_angle")),
    _dilation_angle(getParam<Real>("dilation_angle")),
    _convert_to_radians(getParam<bool>("convert_to_radians")),
    _eqps(declareProperty<Real>("eq_plastic_strain")),
    _eqps_old(getMaterialPropertyOld<Real>("eq_plastic_strain")),
    _elastic_strain_old(getMaterialPropertyOld<RankTwoTensor>(_base_name + "elastic_strain"))
{
  // load the behaviour
  std::string behaviour_name = "NonAssociativeDruckerPrager";
  _b = mgis::behaviour::load(
      _mfront_lib_name, behaviour_name, mgis::behaviour::Hypothesis::TRIDIMENSIONAL);

  if (_convert_to_radians)
  {
    _friction_angle *= libMesh::pi / 180;
    _dilation_angle *= libMesh::pi / 180;
  }
  if (_friction_angle < 0.0 || _dilation_angle < 0.0 || _friction_angle > libMesh::pi / 2.0 ||
      _dilation_angle > libMesh::pi / 2.0)
    mooseError(name(), ": both friction and dilation angles must lie in [0, Pi/2]... aborting.");
  if (_friction_angle < _dilation_angle)
    mooseError(name(), ": friction angle should not be smaller than dilation angle ... aborting.");
  if (_cohesion < 0.0)
    mooseError(name(), ": cohesion should not be negative ... aborting.");
}

void
MFrontNonAssociativeDruckerPrager::initQpStatefulProperties()
{
  _eqps[_qp] = 0.0;
  ComputeStressBase::initQpStatefulProperties();
}

void
MFrontNonAssociativeDruckerPrager::setMaterialProperties(mgis::behaviour::BehaviourData & bd)
{
  bd.s1.material_properties = {
      _young_modulus, _poisson_ratio, _cohesion, _friction_angle, _dilation_angle};
}

void
MFrontNonAssociativeDruckerPrager::setInternalStateVariables(mgis::behaviour::BehaviourData & bd)
{
  bd.s0.internal_state_variables = {_elastic_strain_old[_qp](0, 0),
                                    _elastic_strain_old[_qp](1, 1),
                                    _elastic_strain_old[_qp](2, 2),
                                    _elastic_strain_old[_qp](0, 1),
                                    _elastic_strain_old[_qp](0, 2),
                                    _elastic_strain_old[_qp](1, 2),
                                    _eqps_old[_qp]};
}

void
MFrontNonAssociativeDruckerPrager::updateStateFromMFront(mgis::behaviour::BehaviourData & bd)
{
  // update the stress tensor
  _stress[_qp] = RankTwoTensor(bd.s1.thermodynamic_forces[0],
                               bd.s1.thermodynamic_forces[1],
                               bd.s1.thermodynamic_forces[2],
                               bd.s1.thermodynamic_forces[5],
                               bd.s1.thermodynamic_forces[4],
                               bd.s1.thermodynamic_forces[3]);
  // update the internal state variables
  _elastic_strain[_qp] = RankTwoTensor(bd.s1.internal_state_variables[0],
                                       bd.s1.internal_state_variables[1],
                                       bd.s1.internal_state_variables[2],
                                       bd.s1.internal_state_variables[5],
                                       bd.s1.internal_state_variables[4],
                                       bd.s1.internal_state_variables[3]);
  _eqps[_qp] = bd.s1.internal_state_variables[6];
  // update the tangent stiffness vector
  _Jacobian_mult[_qp].fillSymmetric21FromInputVector(std::array<Real, 21>{{
      bd.K[0],        // C1111
      bd.K[1],        // C1122
      bd.K[2],        // C1133
      bd.K[3],        // C1123
      bd.K[4],        // C1113
      bd.K[5],        // C1112
      bd.K[7],        // C2222
      bd.K[8],        // C2233
      bd.K[9],        // C2223
      bd.K[10],       // C2213
      bd.K[11],       // C2212
      bd.K[14],       // C3333
      bd.K[15],       // C3323
      bd.K[16],       // C3313
      bd.K[17],       // C3312
      0.5 * bd.K[21], // C2323
      0.5 * bd.K[22], // C2313
      0.5 * bd.K[23], // C2312
      0.5 * bd.K[28], // C1313
      0.5 * bd.K[29], // C1312
      0.5 * bd.K[35]  // C1212
  }});
}
