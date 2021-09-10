//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MFrontStressBase.h"
#include "Factory.h"
#include "MooseMesh.h"
#include "RankTwoTensor.h"
#include "RankFourTensor.h"

InputParameters
MFrontStressBase::validParams()
{
  InputParameters params = ComputeStressBase::validParams();
  params.addClassDescription("Base class for coupling material to use mfront models in MOOSE");
  params.addRequiredParam<std::string>("mfront_lib_name",
                                       "The name (full path) of the m_front library.");
  return params;
}

MFrontStressBase::MFrontStressBase(const InputParameters & parameters)
  : ComputeStressBase(parameters),
    _mfront_lib_name(getParam<std::string>("mfront_lib_name")),
    _total_strain(getMaterialProperty<RankTwoTensor>(_base_name + "total_strain")),
    _total_strain_old(getMaterialPropertyOld<RankTwoTensor>(_base_name + "total_strain"))
{
}

void
MFrontStressBase::computeProperties()
{
  // for (auto const & iv : b.isvs)
  // {
  //   auto const name = iv.name;
  //   auto const offset = mgis::behaviour::getVariableOffset(b.isvs, name, b.hypothesis);
  //   auto const size = mgis::behaviour::getVariableSize(iv, b.hypothesis);
  //   printf("name = %s - offset = %i - size = %i\n",
  //          name.c_str(),
  //          static_cast<int>(offset),
  //          static_cast<int>(size));
  // }
  // mooseError("end.");

  // initialize the behaviour data on the current element
  auto bd = mgis::behaviour::BehaviourData{_b};
  // loop @ quadrature points
  for (_qp = 0; _qp < _qrule->n_points(); ++_qp)
  {
    // fill in the behaviour data
    bd.dt = _dt;
    bd.rdt = 1.0;
    bd.K[0] = 4.0; // require consistent tangent operator
    // set material properties
    setMaterialProperties(bd);
    // set internal state variables
    setInternalStateVariables(bd);
    // set external state variables
    setExternalStateVariables(bd);
    // set gradients
    setGradients(bd);
    // set thermodynamic forces
    setThermodynamicForces(bd);
    // initialize the material data view
    auto mv = mgis::behaviour::make_view(bd);
    // do the actual integration
    auto const status = mgis::behaviour::integrate(mv, _b);
    if (status != 1)
      mooseError(name(), ": MFront: integration failed with status ", std::to_string(status));
    // update the new state
    updateStateFromMFront(bd);
    // add in extra stress
    // here since we do not call computeQpProperties in the base material
    _stress[_qp] += _extra_stress[_qp];
  }
}

void
MFrontStressBase::setGradients(mgis::behaviour::BehaviourData & bd)
{
  bd.s0.gradients = {_total_strain_old[_qp](0, 0),
                     _total_strain_old[_qp](1, 1),
                     _total_strain_old[_qp](2, 2),
                     _total_strain_old[_qp](0, 1),
                     _total_strain_old[_qp](0, 2),
                     _total_strain_old[_qp](1, 2)};
  bd.s1.gradients = {_total_strain[_qp](0, 0),
                     _total_strain[_qp](1, 1),
                     _total_strain[_qp](2, 2),
                     _total_strain[_qp](0, 1),
                     _total_strain[_qp](0, 2),
                     _total_strain[_qp](1, 2)};
}
