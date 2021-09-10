//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MFrontLinearElasticity.h"

registerMooseObject("TensorMechanicsApp", MFrontLinearElasticity);

InputParameters
MFrontLinearElasticity::validParams()
{
  InputParameters params = MFrontStressBase::validParams();
  params.addClassDescription("mfront model - linear elasticity.");
  params.addRequiredParam<Real>("young_modulus", "The Young modulus.");
  params.addRequiredParam<Real>("poisson_ratio", "The Poisson ratio.");
  return params;
}

MFrontLinearElasticity::MFrontLinearElasticity(const InputParameters & parameters)
  : MFrontStressBase(parameters),
    _young_modulus(getParam<Real>("young_modulus")),
    _poisson_ratio(getParam<Real>("poisson_ratio"))
{
  std::string behaviour_name = "LinearElasticity";
  _b = mgis::behaviour::load(
      _mfront_lib_name, behaviour_name, mgis::behaviour::Hypothesis::TRIDIMENSIONAL);
}

void
MFrontLinearElasticity::setMaterialProperties(mgis::behaviour::BehaviourData & bd)
{
  bd.s1.material_properties = {_young_modulus, _poisson_ratio};
}

void
MFrontLinearElasticity::updateStateFromMFront(mgis::behaviour::BehaviourData & bd)
{
  Real one_on_sqrt_two = 1.0; // / std::sqrt(2);
  // update the new stress state
  _stress[_qp] = RankTwoTensor(bd.s1.thermodynamic_forces[0],
                               bd.s1.thermodynamic_forces[1],
                               bd.s1.thermodynamic_forces[2],
                               one_on_sqrt_two * bd.s1.thermodynamic_forces[5],
                               one_on_sqrt_two * bd.s1.thermodynamic_forces[4],
                               one_on_sqrt_two * bd.s1.thermodynamic_forces[3]);
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
