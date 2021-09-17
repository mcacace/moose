/*!
* \file   LinearElasticity-generic.cxx
* \brief  This file implements the umat interface for the LinearElasticity behaviour law
* \author Helfer Thomas
* \date   23 / 11 / 06
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
#include"TFEL/Material/LinearElasticity.hxx"
#include"MFront/GenericBehaviour/Integrate.hxx"

#include"MFront/GenericBehaviour/LinearElasticity-generic.hxx"

static tfel::material::OutOfBoundsPolicy&
LinearElasticity_getOutOfBoundsPolicy(){
using namespace tfel::material;
static OutOfBoundsPolicy policy = None;
return policy;
}

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

MFRONT_SHAREDOBJ const char* 
LinearElasticity_build_id = "";

MFRONT_SHAREDOBJ const char* 
LinearElasticity_mfront_ept = "LinearElasticity";

MFRONT_SHAREDOBJ const char* 
LinearElasticity_tfel_version = "4.0.0-dev";

MFRONT_SHAREDOBJ unsigned short LinearElasticity_mfront_mkt = 1u;

MFRONT_SHAREDOBJ const char *
LinearElasticity_mfront_interface = "Generic";

MFRONT_SHAREDOBJ const char *
LinearElasticity_src = "LinearElasticity.mfront";

MFRONT_SHAREDOBJ unsigned short LinearElasticity_nModellingHypotheses = 5u;

MFRONT_SHAREDOBJ const char * 
LinearElasticity_ModellingHypotheses[5u] = {"AxisymmetricalGeneralisedPlaneStrain",
"Axisymmetrical",
"PlaneStrain",
"GeneralisedPlaneStrain",
"Tridimensional"};

MFRONT_SHAREDOBJ unsigned short LinearElasticity_nMainVariables = 1;
MFRONT_SHAREDOBJ unsigned short LinearElasticity_nGradients = 1;

MFRONT_SHAREDOBJ int LinearElasticity_GradientsTypes[1] = {1};
MFRONT_SHAREDOBJ const char * LinearElasticity_Gradients[1] = {"Strain"};
MFRONT_SHAREDOBJ unsigned short LinearElasticity_nThermodynamicForces = 1;

MFRONT_SHAREDOBJ int LinearElasticity_ThermodynamicForcesTypes[1] = {1};
MFRONT_SHAREDOBJ const char * LinearElasticity_ThermodynamicForces[1] = {"Stress"};
MFRONT_SHAREDOBJ unsigned short LinearElasticity_nTangentOperatorBlocks = 2;

MFRONT_SHAREDOBJ const char * LinearElasticity_TangentOperatorBlocks[2] = {"Stress",
"Strain"};
MFRONT_SHAREDOBJ unsigned short LinearElasticity_BehaviourType = 1u;

MFRONT_SHAREDOBJ unsigned short LinearElasticity_BehaviourKinematic = 1u;

MFRONT_SHAREDOBJ unsigned short LinearElasticity_SymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short LinearElasticity_ElasticSymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short LinearElasticity_api_version = 1u;

MFRONT_SHAREDOBJ unsigned short LinearElasticity_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short LinearElasticity_nMaterialProperties = 2u;

MFRONT_SHAREDOBJ const char *LinearElasticity_MaterialProperties[2u] = {"YoungModulus",
"PoissonRatio"};

MFRONT_SHAREDOBJ unsigned short LinearElasticity_nInternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * LinearElasticity_InternalStateVariables = nullptr;

MFRONT_SHAREDOBJ const int * LinearElasticity_InternalStateVariablesTypes = nullptr;

MFRONT_SHAREDOBJ unsigned short LinearElasticity_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * LinearElasticity_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short LinearElasticity_nParameters = 2;
MFRONT_SHAREDOBJ const char * LinearElasticity_Parameters[2] = {"minimal_time_step_scaling_factor",
"maximal_time_step_scaling_factor"};
MFRONT_SHAREDOBJ int LinearElasticity_ParametersTypes [] = {0,0};

MFRONT_SHAREDOBJ double LinearElasticity_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double LinearElasticity_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ unsigned short LinearElasticity_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short LinearElasticity_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short LinearElasticity_nInitializeFunctions= 0;

MFRONT_SHAREDOBJ const char * const * LinearElasticity_InitializeFunctions = nullptr;


MFRONT_SHAREDOBJ unsigned short LinearElasticity_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short LinearElasticity_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ void
LinearElasticity_setOutOfBoundsPolicy(const int p){
if(p==0){
LinearElasticity_getOutOfBoundsPolicy() = tfel::material::None;
} else if(p==1){
LinearElasticity_getOutOfBoundsPolicy() = tfel::material::Warning;
} else if(p==2){
LinearElasticity_getOutOfBoundsPolicy() = tfel::material::Strict;
} else {
std::cerr << "LinearElasticity_setOutOfBoundsPolicy: invalid argument\n";
}
}

MFRONT_SHAREDOBJ int
LinearElasticity_setParameter(const char *const key,const double value){
using tfel::material::LinearElasticityParametersInitializer;
auto& i = LinearElasticityParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int LinearElasticity_AxisymmetricalGeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRAIN;
using Behaviour = LinearElasticity<h,real,true>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, LinearElasticity_getOutOfBoundsPolicy());
return r;
} // end of LinearElasticity_AxisymmetricalGeneralisedPlaneStrain

MFRONT_SHAREDOBJ int LinearElasticity_Axisymmetrical(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICAL;
using Behaviour = LinearElasticity<h,real,true>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, LinearElasticity_getOutOfBoundsPolicy());
return r;
} // end of LinearElasticity_Axisymmetrical

MFRONT_SHAREDOBJ int LinearElasticity_PlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::PLANESTRAIN;
using Behaviour = LinearElasticity<h,real,true>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, LinearElasticity_getOutOfBoundsPolicy());
return r;
} // end of LinearElasticity_PlaneStrain

MFRONT_SHAREDOBJ int LinearElasticity_GeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::GENERALISEDPLANESTRAIN;
using Behaviour = LinearElasticity<h,real,true>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, LinearElasticity_getOutOfBoundsPolicy());
return r;
} // end of LinearElasticity_GeneralisedPlaneStrain

MFRONT_SHAREDOBJ int LinearElasticity_Tridimensional(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::TRIDIMENSIONAL;
using Behaviour = LinearElasticity<h,real,true>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, LinearElasticity_getOutOfBoundsPolicy());
return r;
} // end of LinearElasticity_Tridimensional

#ifdef __cplusplus
}
#endif /* __cplusplus */

