/*!
* \file   Marigo-generic.cxx
* \brief  This file implements the umat interface for the Marigo behaviour law
* \author Thomas Helfer
* \date   1 / 12 / 2016
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
#include"TFEL/Material/Marigo.hxx"
#include"MFront/GenericBehaviour/Integrate.hxx"

#include"MFront/GenericBehaviour/Marigo-generic.hxx"

static tfel::material::OutOfBoundsPolicy&
Marigo_getOutOfBoundsPolicy(){
using namespace tfel::material;
static OutOfBoundsPolicy policy = None;
return policy;
}

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

MFRONT_SHAREDOBJ const char* 
Marigo_build_id = "";

MFRONT_SHAREDOBJ const char* 
Marigo_mfront_ept = "Marigo";

MFRONT_SHAREDOBJ const char* 
Marigo_tfel_version = "4.0.0-dev";

MFRONT_SHAREDOBJ unsigned short Marigo_mfront_mkt = 1u;

MFRONT_SHAREDOBJ const char *
Marigo_mfront_interface = "Generic";

MFRONT_SHAREDOBJ const char *
Marigo_src = "Marigo.mfront";

MFRONT_SHAREDOBJ unsigned short Marigo_nModellingHypotheses = 5u;

MFRONT_SHAREDOBJ const char * 
Marigo_ModellingHypotheses[5u] = {"AxisymmetricalGeneralisedPlaneStrain",
"Axisymmetrical",
"PlaneStrain",
"GeneralisedPlaneStrain",
"Tridimensional"};

MFRONT_SHAREDOBJ unsigned short Marigo_nMainVariables = 1;
MFRONT_SHAREDOBJ unsigned short Marigo_nGradients = 1;

MFRONT_SHAREDOBJ int Marigo_GradientsTypes[1] = {1};
MFRONT_SHAREDOBJ const char * Marigo_Gradients[1] = {"Strain"};
MFRONT_SHAREDOBJ unsigned short Marigo_nThermodynamicForces = 1;

MFRONT_SHAREDOBJ int Marigo_ThermodynamicForcesTypes[1] = {1};
MFRONT_SHAREDOBJ const char * Marigo_ThermodynamicForces[1] = {"Stress"};
MFRONT_SHAREDOBJ unsigned short Marigo_nTangentOperatorBlocks = 2;

MFRONT_SHAREDOBJ const char * Marigo_TangentOperatorBlocks[2] = {"Stress",
"Strain"};
MFRONT_SHAREDOBJ unsigned short Marigo_BehaviourType = 1u;

MFRONT_SHAREDOBJ unsigned short Marigo_BehaviourKinematic = 1u;

MFRONT_SHAREDOBJ unsigned short Marigo_SymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short Marigo_ElasticSymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short Marigo_api_version = 1u;

MFRONT_SHAREDOBJ unsigned short Marigo_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short Marigo_nMaterialProperties = 2u;

MFRONT_SHAREDOBJ const char *Marigo_MaterialProperties[2u] = {"YoungModulus",
"PoissonRatio"};

MFRONT_SHAREDOBJ unsigned short Marigo_nInternalStateVariables = 1;
MFRONT_SHAREDOBJ const char * Marigo_InternalStateVariables[1] = {"Damage"};
MFRONT_SHAREDOBJ int Marigo_InternalStateVariablesTypes [] = {0};

MFRONT_SHAREDOBJ unsigned short Marigo_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * Marigo_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short Marigo_nParameters = 4;
MFRONT_SHAREDOBJ const char * Marigo_Parameters[4] = {"Yw",
"g","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor"};
MFRONT_SHAREDOBJ int Marigo_ParametersTypes [] = {0,0,0,0};

MFRONT_SHAREDOBJ double Marigo_Yw_ParameterDefaultValue = 75000;

MFRONT_SHAREDOBJ double Marigo_g_ParameterDefaultValue = 0.2;

MFRONT_SHAREDOBJ double Marigo_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double Marigo_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ unsigned short Marigo_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short Marigo_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short Marigo_nInitializeFunctions= 0;

MFRONT_SHAREDOBJ const char * const * Marigo_InitializeFunctions = nullptr;


MFRONT_SHAREDOBJ unsigned short Marigo_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short Marigo_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ void
Marigo_setOutOfBoundsPolicy(const int p){
if(p==0){
Marigo_getOutOfBoundsPolicy() = tfel::material::None;
} else if(p==1){
Marigo_getOutOfBoundsPolicy() = tfel::material::Warning;
} else if(p==2){
Marigo_getOutOfBoundsPolicy() = tfel::material::Strict;
} else {
std::cerr << "Marigo_setOutOfBoundsPolicy: invalid argument\n";
}
}

MFRONT_SHAREDOBJ int
Marigo_setParameter(const char *const key,const double value){
using tfel::material::MarigoParametersInitializer;
auto& i = MarigoParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int Marigo_AxisymmetricalGeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRAIN;
using Behaviour = Marigo<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, Marigo_getOutOfBoundsPolicy());
return r;
} // end of Marigo_AxisymmetricalGeneralisedPlaneStrain

MFRONT_SHAREDOBJ int Marigo_Axisymmetrical(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICAL;
using Behaviour = Marigo<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, Marigo_getOutOfBoundsPolicy());
return r;
} // end of Marigo_Axisymmetrical

MFRONT_SHAREDOBJ int Marigo_PlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::PLANESTRAIN;
using Behaviour = Marigo<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, Marigo_getOutOfBoundsPolicy());
return r;
} // end of Marigo_PlaneStrain

MFRONT_SHAREDOBJ int Marigo_GeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::GENERALISEDPLANESTRAIN;
using Behaviour = Marigo<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, Marigo_getOutOfBoundsPolicy());
return r;
} // end of Marigo_GeneralisedPlaneStrain

MFRONT_SHAREDOBJ int Marigo_Tridimensional(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::TRIDIMENSIONAL;
using Behaviour = Marigo<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, Marigo_getOutOfBoundsPolicy());
return r;
} // end of Marigo_Tridimensional

#ifdef __cplusplus
}
#endif /* __cplusplus */

