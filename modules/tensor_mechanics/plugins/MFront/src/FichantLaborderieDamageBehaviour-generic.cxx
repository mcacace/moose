/*!
* \file   FichantLaborderieDamageBehaviour-generic.cxx
* \brief  This file implements the umat interface for the FichantLaborderieDamageBehaviour behaviour law
* \author A . Gangnant , T . Helfer
* \date   7 / 12 / 2019
*/

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif /* NOMINMAX */
#include <windows.h>
#ifdef small
#undef small
#endif /* small */
#endif /* _WIN32 */

#ifndef MFRONT_SHAREDOBJ
#define MFRONT_SHAREDOBJ TFEL_VISIBILITY_EXPORT
#endif /* MFRONT_SHAREDOBJ */

#include<iostream>
#include<cstdlib>
#include"TFEL/Material/OutOfBoundsPolicy.hxx"
#include"TFEL/Math/t2tot2.hxx"
#include"TFEL/Math/t2tost2.hxx"
#include"TFEL/Material/FichantLaborderieDamageBehaviour.hxx"
#include"MFront/GenericBehaviour/Integrate.hxx"

#include"MFront/GenericBehaviour/FichantLaborderieDamageBehaviour-generic.hxx"

static tfel::material::OutOfBoundsPolicy&
FichantLaborderieDamageBehaviour_getOutOfBoundsPolicy(){
using namespace tfel::material;
static OutOfBoundsPolicy policy = None;
return policy;
}

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

MFRONT_SHAREDOBJ const char* 
FichantLaborderieDamageBehaviour_build_id = "";

MFRONT_SHAREDOBJ const char* 
FichantLaborderieDamageBehaviour_mfront_ept = "FichantLaborderieDamageBehaviour";

MFRONT_SHAREDOBJ const char* 
FichantLaborderieDamageBehaviour_tfel_version = "4.0.0-dev";

MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_mfront_mkt = 1u;

MFRONT_SHAREDOBJ const char *
FichantLaborderieDamageBehaviour_mfront_interface = "Generic";

MFRONT_SHAREDOBJ const char *
FichantLaborderieDamageBehaviour_src = "FichantLaBorderieDamageBehaviour.mfront";

MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_nModellingHypotheses = 5u;

MFRONT_SHAREDOBJ const char * 
FichantLaborderieDamageBehaviour_ModellingHypotheses[5u] = {"AxisymmetricalGeneralisedPlaneStrain",
"Axisymmetrical",
"PlaneStrain",
"GeneralisedPlaneStrain",
"Tridimensional"};

MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_nMainVariables = 1;
MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_nGradients = 1;

MFRONT_SHAREDOBJ int FichantLaborderieDamageBehaviour_GradientsTypes[1] = {1};
MFRONT_SHAREDOBJ const char * FichantLaborderieDamageBehaviour_Gradients[1] = {"Strain"};
MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_nThermodynamicForces = 1;

MFRONT_SHAREDOBJ int FichantLaborderieDamageBehaviour_ThermodynamicForcesTypes[1] = {1};
MFRONT_SHAREDOBJ const char * FichantLaborderieDamageBehaviour_ThermodynamicForces[1] = {"Stress"};
MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_nTangentOperatorBlocks = 2;

MFRONT_SHAREDOBJ const char * FichantLaborderieDamageBehaviour_TangentOperatorBlocks[2] = {"Stress",
"Strain"};
MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_BehaviourType = 1u;

MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_BehaviourKinematic = 1u;

MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_SymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_ElasticSymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_api_version = 1u;

MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_nMaterialProperties = 5u;

MFRONT_SHAREDOBJ const char *FichantLaborderieDamageBehaviour_MaterialProperties[5u] = {"YoungModulus",
"PoissonRatio",
"Bt",
"e0",
"a"};

MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_nInternalStateVariables = 1;
MFRONT_SHAREDOBJ const char * FichantLaborderieDamageBehaviour_InternalStateVariables[1] = {"Damage"};
MFRONT_SHAREDOBJ int FichantLaborderieDamageBehaviour_InternalStateVariablesTypes [] = {0};

MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * FichantLaborderieDamageBehaviour_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_nParameters = 2;
MFRONT_SHAREDOBJ const char * FichantLaborderieDamageBehaviour_Parameters[2] = {"minimal_time_step_scaling_factor",
"maximal_time_step_scaling_factor"};
MFRONT_SHAREDOBJ int FichantLaborderieDamageBehaviour_ParametersTypes [] = {0,0};

MFRONT_SHAREDOBJ double FichantLaborderieDamageBehaviour_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double FichantLaborderieDamageBehaviour_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_nInitializeFunctions= 0;

MFRONT_SHAREDOBJ const char * const * FichantLaborderieDamageBehaviour_InitializeFunctions = nullptr;


MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short FichantLaborderieDamageBehaviour_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ void
FichantLaborderieDamageBehaviour_setOutOfBoundsPolicy(const int p){
if(p==0){
FichantLaborderieDamageBehaviour_getOutOfBoundsPolicy() = tfel::material::None;
} else if(p==1){
FichantLaborderieDamageBehaviour_getOutOfBoundsPolicy() = tfel::material::Warning;
} else if(p==2){
FichantLaborderieDamageBehaviour_getOutOfBoundsPolicy() = tfel::material::Strict;
} else {
std::cerr << "FichantLaborderieDamageBehaviour_setOutOfBoundsPolicy: invalid argument\n";
}
}

MFRONT_SHAREDOBJ int
FichantLaborderieDamageBehaviour_setParameter(const char *const key,const double value){
using tfel::material::FichantLaborderieDamageBehaviourParametersInitializer;
auto& i = FichantLaborderieDamageBehaviourParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int FichantLaborderieDamageBehaviour_AxisymmetricalGeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRAIN;
using Behaviour = FichantLaborderieDamageBehaviour<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, FichantLaborderieDamageBehaviour_getOutOfBoundsPolicy());
return r;
} // end of FichantLaborderieDamageBehaviour_AxisymmetricalGeneralisedPlaneStrain

MFRONT_SHAREDOBJ int FichantLaborderieDamageBehaviour_Axisymmetrical(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICAL;
using Behaviour = FichantLaborderieDamageBehaviour<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, FichantLaborderieDamageBehaviour_getOutOfBoundsPolicy());
return r;
} // end of FichantLaborderieDamageBehaviour_Axisymmetrical

MFRONT_SHAREDOBJ int FichantLaborderieDamageBehaviour_PlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::PLANESTRAIN;
using Behaviour = FichantLaborderieDamageBehaviour<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, FichantLaborderieDamageBehaviour_getOutOfBoundsPolicy());
return r;
} // end of FichantLaborderieDamageBehaviour_PlaneStrain

MFRONT_SHAREDOBJ int FichantLaborderieDamageBehaviour_GeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::GENERALISEDPLANESTRAIN;
using Behaviour = FichantLaborderieDamageBehaviour<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, FichantLaborderieDamageBehaviour_getOutOfBoundsPolicy());
return r;
} // end of FichantLaborderieDamageBehaviour_GeneralisedPlaneStrain

MFRONT_SHAREDOBJ int FichantLaborderieDamageBehaviour_Tridimensional(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::TRIDIMENSIONAL;
using Behaviour = FichantLaborderieDamageBehaviour<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, FichantLaborderieDamageBehaviour_getOutOfBoundsPolicy());
return r;
} // end of FichantLaborderieDamageBehaviour_Tridimensional

#ifdef __cplusplus
}
#endif /* __cplusplus */

