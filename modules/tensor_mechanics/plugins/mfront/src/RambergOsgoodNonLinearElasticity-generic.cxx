/*!
* \file   RambergOsgoodNonLinearElasticity-generic.cxx
* \brief  This file implements the umat interface for the RambergOsgoodNonLinearElasticity behaviour law
* \author L . Gelebart / V . Duc Nguyen
* \date   
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
#include"TFEL/Material/RambergOsgoodNonLinearElasticity.hxx"
#include"MFront/GenericBehaviour/Integrate.hxx"

#include"MFront/GenericBehaviour/RambergOsgoodNonLinearElasticity-generic.hxx"

static tfel::material::OutOfBoundsPolicy&
RambergOsgoodNonLinearElasticity_getOutOfBoundsPolicy(){
using namespace tfel::material;
static OutOfBoundsPolicy policy = None;
return policy;
}

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

MFRONT_SHAREDOBJ const char* 
RambergOsgoodNonLinearElasticity_build_id = "";

MFRONT_SHAREDOBJ const char* 
RambergOsgoodNonLinearElasticity_mfront_ept = "RambergOsgoodNonLinearElasticity";

MFRONT_SHAREDOBJ const char* 
RambergOsgoodNonLinearElasticity_tfel_version = "4.0.0-dev";

MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_mfront_mkt = 1u;

MFRONT_SHAREDOBJ const char *
RambergOsgoodNonLinearElasticity_mfront_interface = "Generic";

MFRONT_SHAREDOBJ const char *
RambergOsgoodNonLinearElasticity_src = "RambergOsgoodNonLinearElasticity.mfront";

MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_nModellingHypotheses = 5u;

MFRONT_SHAREDOBJ const char * 
RambergOsgoodNonLinearElasticity_ModellingHypotheses[5u] = {"AxisymmetricalGeneralisedPlaneStrain",
"Axisymmetrical",
"PlaneStrain",
"GeneralisedPlaneStrain",
"Tridimensional"};

MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_nMainVariables = 1;
MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_nGradients = 1;

MFRONT_SHAREDOBJ int RambergOsgoodNonLinearElasticity_GradientsTypes[1] = {1};
MFRONT_SHAREDOBJ const char * RambergOsgoodNonLinearElasticity_Gradients[1] = {"Strain"};
MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_nThermodynamicForces = 1;

MFRONT_SHAREDOBJ int RambergOsgoodNonLinearElasticity_ThermodynamicForcesTypes[1] = {1};
MFRONT_SHAREDOBJ const char * RambergOsgoodNonLinearElasticity_ThermodynamicForces[1] = {"Stress"};
MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_nTangentOperatorBlocks = 2;

MFRONT_SHAREDOBJ const char * RambergOsgoodNonLinearElasticity_TangentOperatorBlocks[2] = {"Stress",
"Strain"};
MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_BehaviourType = 1u;

MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_BehaviourKinematic = 1u;

MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_SymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_ElasticSymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_api_version = 1u;

MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_nMaterialProperties = 5u;

MFRONT_SHAREDOBJ const char *RambergOsgoodNonLinearElasticity_MaterialProperties[5u] = {"YoungModulus",
"PoissonRatio",
"n",
"alpha",
"YieldStrength"};

MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_nInternalStateVariables = 1;
MFRONT_SHAREDOBJ const char * RambergOsgoodNonLinearElasticity_InternalStateVariables[1] = {"VonMisesStress"};
MFRONT_SHAREDOBJ int RambergOsgoodNonLinearElasticity_InternalStateVariablesTypes [] = {0};

MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * RambergOsgoodNonLinearElasticity_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_nParameters = 3;
MFRONT_SHAREDOBJ const char * RambergOsgoodNonLinearElasticity_Parameters[3] = {"NumericalThreshold",
"minimal_time_step_scaling_factor","maximal_time_step_scaling_factor"};
MFRONT_SHAREDOBJ int RambergOsgoodNonLinearElasticity_ParametersTypes [] = {0,0,0};

MFRONT_SHAREDOBJ double RambergOsgoodNonLinearElasticity_NumericalThreshold_ParameterDefaultValue = 1e-12;

MFRONT_SHAREDOBJ double RambergOsgoodNonLinearElasticity_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double RambergOsgoodNonLinearElasticity_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_nInitializeFunctions= 0;

MFRONT_SHAREDOBJ const char * const * RambergOsgoodNonLinearElasticity_InitializeFunctions = nullptr;


MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short RambergOsgoodNonLinearElasticity_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ void
RambergOsgoodNonLinearElasticity_setOutOfBoundsPolicy(const int p){
if(p==0){
RambergOsgoodNonLinearElasticity_getOutOfBoundsPolicy() = tfel::material::None;
} else if(p==1){
RambergOsgoodNonLinearElasticity_getOutOfBoundsPolicy() = tfel::material::Warning;
} else if(p==2){
RambergOsgoodNonLinearElasticity_getOutOfBoundsPolicy() = tfel::material::Strict;
} else {
std::cerr << "RambergOsgoodNonLinearElasticity_setOutOfBoundsPolicy: invalid argument\n";
}
}

MFRONT_SHAREDOBJ int
RambergOsgoodNonLinearElasticity_setParameter(const char *const key,const double value){
using tfel::material::RambergOsgoodNonLinearElasticityParametersInitializer;
auto& i = RambergOsgoodNonLinearElasticityParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int RambergOsgoodNonLinearElasticity_AxisymmetricalGeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRAIN;
using Behaviour = RambergOsgoodNonLinearElasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, RambergOsgoodNonLinearElasticity_getOutOfBoundsPolicy());
return r;
} // end of RambergOsgoodNonLinearElasticity_AxisymmetricalGeneralisedPlaneStrain

MFRONT_SHAREDOBJ int RambergOsgoodNonLinearElasticity_Axisymmetrical(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICAL;
using Behaviour = RambergOsgoodNonLinearElasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, RambergOsgoodNonLinearElasticity_getOutOfBoundsPolicy());
return r;
} // end of RambergOsgoodNonLinearElasticity_Axisymmetrical

MFRONT_SHAREDOBJ int RambergOsgoodNonLinearElasticity_PlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::PLANESTRAIN;
using Behaviour = RambergOsgoodNonLinearElasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, RambergOsgoodNonLinearElasticity_getOutOfBoundsPolicy());
return r;
} // end of RambergOsgoodNonLinearElasticity_PlaneStrain

MFRONT_SHAREDOBJ int RambergOsgoodNonLinearElasticity_GeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::GENERALISEDPLANESTRAIN;
using Behaviour = RambergOsgoodNonLinearElasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, RambergOsgoodNonLinearElasticity_getOutOfBoundsPolicy());
return r;
} // end of RambergOsgoodNonLinearElasticity_GeneralisedPlaneStrain

MFRONT_SHAREDOBJ int RambergOsgoodNonLinearElasticity_Tridimensional(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::TRIDIMENSIONAL;
using Behaviour = RambergOsgoodNonLinearElasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, RambergOsgoodNonLinearElasticity_getOutOfBoundsPolicy());
return r;
} // end of RambergOsgoodNonLinearElasticity_Tridimensional

#ifdef __cplusplus
}
#endif /* __cplusplus */

