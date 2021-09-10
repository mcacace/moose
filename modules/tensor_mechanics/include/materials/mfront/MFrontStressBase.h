//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "ComputeStressBase.h"
// GMIS include
#include <MGIS/Behaviour/Behaviour.hxx>
#include <MGIS/Behaviour/BehaviourData.hxx>
#include "MGIS/Behaviour/State.hxx"
#include "MGIS/Behaviour/MaterialDataManager.hxx"
#include "MGIS/Behaviour/Integrate.hxx"

/**
 * Coupling material to use Abaqus UMAT models in MOOSE
 */
class MFrontStressBase : public ComputeStressBase
{
public:
  static InputParameters validParams();
  MFrontStressBase(const InputParameters & parameters);
  virtual ~MFrontStressBase(){};
  /// perform per-element computation/initialization
  void computeProperties() override;

protected:
  virtual void computeQpStress() override { mooseError(name(), ": should not be called here!"); };
  // virtual to be overrriden in the corresponding material class implementation
  virtual void setMaterialProperties(mgis::behaviour::BehaviourData & bd) = 0;
  virtual void setInternalStateVariables(mgis::behaviour::BehaviourData & bd) = 0;
  virtual void setExternalStateVariables(mgis::behaviour::BehaviourData & bd) = 0;
  virtual void setThermodynamicForces(mgis::behaviour::BehaviourData & bd) = 0;
  virtual void updateStateFromMFront(mgis::behaviour::BehaviourData & bd) = 0;

  void setGradients(mgis::behaviour::BehaviourData & bd);

  // name of the mfront library
  const std::string _mfront_lib_name;
  // mfront behaviour
  mgis::behaviour::Behaviour _b;

  // basic materials for mfront
  const MaterialProperty<RankTwoTensor> & _total_strain;
  const MaterialProperty<RankTwoTensor> & _total_strain_old;
};
