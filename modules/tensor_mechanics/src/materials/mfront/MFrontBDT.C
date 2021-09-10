//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MFrontBDT.h"

registerMooseObject("TensorMechanicsApp", MFrontBDT);

// MFront (Tensor convention): 11 22 33 12 13 23
// Moose (Tensor convention):  11 22 33 23 13 12

InputParameters
MFrontBDT::validParams()
{
  InputParameters params = MFrontStressBase::validParams();
  params.addClassDescription("mfront model - linear elasticity.");
  params.addRequiredParam<Real>("young_modulus", "The Young modulus.");
  params.addRequiredParam<Real>("poisson_ratio", "The Poisson ratio.");
  return params;
}

MFrontBDT::MFrontBDT(const InputParameters & parameters)
  : MFrontStressBase(parameters),
    _young_modulus(getParam<Real>("young_modulus")),
    _poisson_ratio(getParam<Real>("poisson_ratio"))
{
  std::string behaviour_name = "BDT";
  _b = mgis::behaviour::load(
      _mfront_lib_name, behaviour_name, mgis::behaviour::Hypothesis::TRIDIMENSIONAL);
}
