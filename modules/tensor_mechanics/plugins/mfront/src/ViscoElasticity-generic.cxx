/*!
* \file   ViscoElasticity-generic.cxx
* \brief  This file implements the umat interface for the ViscoElasticity behaviour law
* \author 
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
#include"TFEL/Material/ViscoElasticity.hxx"
#include"MFront/GenericBehaviour/Integrate.hxx"

#include"MFront/GenericBehaviour/ViscoElasticity-generic.hxx"

static tfel::material::OutOfBoundsPolicy&
ViscoElasticity_getOutOfBoundsPolicy(){
using namespace tfel::material;
static OutOfBoundsPolicy policy = None;
return policy;
}

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

MFRONT_SHAREDOBJ const char* 
ViscoElasticity_build_id = "";

MFRONT_SHAREDOBJ const char* 
ViscoElasticity_mfront_ept = "ViscoElasticity";

MFRONT_SHAREDOBJ const char* 
ViscoElasticity_tfel_version = "4.0.0-dev";

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_mfront_mkt = 1u;

MFRONT_SHAREDOBJ const char *
ViscoElasticity_mfront_interface = "Generic";

MFRONT_SHAREDOBJ const char *
ViscoElasticity_src = "ViscoElasticity.mfront";

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_nModellingHypotheses = 7u;

MFRONT_SHAREDOBJ const char * 
ViscoElasticity_ModellingHypotheses[7u] = {"AxisymmetricalGeneralisedPlaneStrain",
"AxisymmetricalGeneralisedPlaneStress",
"Axisymmetrical",
"PlaneStress",
"PlaneStrain",
"GeneralisedPlaneStrain",
"Tridimensional"};

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_nMainVariables = 1;
MFRONT_SHAREDOBJ unsigned short ViscoElasticity_nGradients = 1;

MFRONT_SHAREDOBJ int ViscoElasticity_GradientsTypes[1] = {1};
MFRONT_SHAREDOBJ const char * ViscoElasticity_Gradients[1] = {"Strain"};
MFRONT_SHAREDOBJ unsigned short ViscoElasticity_nThermodynamicForces = 1;

MFRONT_SHAREDOBJ int ViscoElasticity_ThermodynamicForcesTypes[1] = {1};
MFRONT_SHAREDOBJ const char * ViscoElasticity_ThermodynamicForces[1] = {"Stress"};
MFRONT_SHAREDOBJ unsigned short ViscoElasticity_nTangentOperatorBlocks = 2;

MFRONT_SHAREDOBJ const char * ViscoElasticity_TangentOperatorBlocks[2] = {"Stress",
"Strain"};
MFRONT_SHAREDOBJ unsigned short ViscoElasticity_BehaviourType = 1u;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_BehaviourKinematic = 1u;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_SymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_ElasticSymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_api_version = 1u;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_nMaterialProperties = 6u;

MFRONT_SHAREDOBJ const char *ViscoElasticity_MaterialProperties[6u] = {"YoungModulus",
"PoissonRatio",
"ActivationEnthalpy",
"PreExponentialConstant",
"Exponent",
"RConstant"};

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_nInternalStateVariables = 2;
MFRONT_SHAREDOBJ const char * ViscoElasticity_InternalStateVariables[2] = {"ElasticStrain",
"EquivalentViscoplasticStrain"};
MFRONT_SHAREDOBJ int ViscoElasticity_InternalStateVariablesTypes [] = {1,0};

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * ViscoElasticity_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_nParameters = 7;
MFRONT_SHAREDOBJ const char * ViscoElasticity_Parameters[7] = {"RelativeValueForTheEquivalentStressLowerBoundDefinition",
"epsilon","theta","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","numerical_jacobian_epsilon",
"iterMax"};
MFRONT_SHAREDOBJ int ViscoElasticity_ParametersTypes [] = {0,0,0,0,0,0,2};

MFRONT_SHAREDOBJ double ViscoElasticity_RelativeValueForTheEquivalentStressLowerBoundDefinition_ParameterDefaultValue = 1e-12;

MFRONT_SHAREDOBJ double ViscoElasticity_epsilon_ParameterDefaultValue = 1e-16;

MFRONT_SHAREDOBJ double ViscoElasticity_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double ViscoElasticity_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double ViscoElasticity_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double ViscoElasticity_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-17;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short ViscoElasticity_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short ViscoElasticity_nInitializeFunctions= 0;

MFRONT_SHAREDOBJ const char * const * ViscoElasticity_InitializeFunctions = nullptr;


MFRONT_SHAREDOBJ unsigned short ViscoElasticity_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_nMaterialProperties = 6u;

MFRONT_SHAREDOBJ const char *ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_MaterialProperties[6u] = {"YoungModulus",
"PoissonRatio",
"ActivationEnthalpy",
"PreExponentialConstant",
"Exponent",
"RConstant"};

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_nInternalStateVariables = 3;
MFRONT_SHAREDOBJ const char * ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_InternalStateVariables[3] = {"ElasticStrain",
"EquivalentViscoplasticStrain","AxialStrain"};
MFRONT_SHAREDOBJ int ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_InternalStateVariablesTypes [] = {1,0,0};

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_nExternalStateVariables = 1;
MFRONT_SHAREDOBJ const char * ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_ExternalStateVariables[1] = {"AxialStress"};
MFRONT_SHAREDOBJ unsigned short ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_nParameters = 7;
MFRONT_SHAREDOBJ const char * ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_Parameters[7] = {"RelativeValueForTheEquivalentStressLowerBoundDefinition",
"epsilon","theta","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","numerical_jacobian_epsilon",
"iterMax"};
MFRONT_SHAREDOBJ int ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_ParametersTypes [] = {0,0,0,0,0,0,2};

MFRONT_SHAREDOBJ double ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_RelativeValueForTheEquivalentStressLowerBoundDefinition_ParameterDefaultValue = 1e-12;

MFRONT_SHAREDOBJ double ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_epsilon_ParameterDefaultValue = 1e-16;

MFRONT_SHAREDOBJ double ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-17;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_nInitializeFunctions= 0;

MFRONT_SHAREDOBJ const char * const * ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_InitializeFunctions = nullptr;


MFRONT_SHAREDOBJ unsigned short ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_PlaneStress_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_PlaneStress_nMaterialProperties = 6u;

MFRONT_SHAREDOBJ const char *ViscoElasticity_PlaneStress_MaterialProperties[6u] = {"YoungModulus",
"PoissonRatio",
"ActivationEnthalpy",
"PreExponentialConstant",
"Exponent",
"RConstant"};

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_PlaneStress_nInternalStateVariables = 3;
MFRONT_SHAREDOBJ const char * ViscoElasticity_PlaneStress_InternalStateVariables[3] = {"ElasticStrain",
"EquivalentViscoplasticStrain","AxialStrain"};
MFRONT_SHAREDOBJ int ViscoElasticity_PlaneStress_InternalStateVariablesTypes [] = {1,0,0};

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_PlaneStress_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * ViscoElasticity_PlaneStress_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_PlaneStress_nParameters = 7;
MFRONT_SHAREDOBJ const char * ViscoElasticity_PlaneStress_Parameters[7] = {"RelativeValueForTheEquivalentStressLowerBoundDefinition",
"epsilon","theta","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","numerical_jacobian_epsilon",
"iterMax"};
MFRONT_SHAREDOBJ int ViscoElasticity_PlaneStress_ParametersTypes [] = {0,0,0,0,0,0,2};

MFRONT_SHAREDOBJ double ViscoElasticity_PlaneStress_RelativeValueForTheEquivalentStressLowerBoundDefinition_ParameterDefaultValue = 1e-12;

MFRONT_SHAREDOBJ double ViscoElasticity_PlaneStress_epsilon_ParameterDefaultValue = 1e-16;

MFRONT_SHAREDOBJ double ViscoElasticity_PlaneStress_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double ViscoElasticity_PlaneStress_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double ViscoElasticity_PlaneStress_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double ViscoElasticity_PlaneStress_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-17;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_PlaneStress_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_PlaneStress_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short ViscoElasticity_PlaneStress_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short ViscoElasticity_PlaneStress_nInitializeFunctions= 0;

MFRONT_SHAREDOBJ const char * const * ViscoElasticity_PlaneStress_InitializeFunctions = nullptr;


MFRONT_SHAREDOBJ unsigned short ViscoElasticity_PlaneStress_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short ViscoElasticity_PlaneStress_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ void
ViscoElasticity_setOutOfBoundsPolicy(const int p){
if(p==0){
ViscoElasticity_getOutOfBoundsPolicy() = tfel::material::None;
} else if(p==1){
ViscoElasticity_getOutOfBoundsPolicy() = tfel::material::Warning;
} else if(p==2){
ViscoElasticity_getOutOfBoundsPolicy() = tfel::material::Strict;
} else {
std::cerr << "ViscoElasticity_setOutOfBoundsPolicy: invalid argument\n";
}
}

MFRONT_SHAREDOBJ int
ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_setParameter(const char *const key,const double value){
using tfel::material::ViscoElasticityAxisymmetricalGeneralisedPlaneStressParametersInitializer;
auto& i = ViscoElasticityAxisymmetricalGeneralisedPlaneStressParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::ViscoElasticityAxisymmetricalGeneralisedPlaneStressParametersInitializer;
auto& i = ViscoElasticityAxisymmetricalGeneralisedPlaneStressParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
ViscoElasticity_PlaneStress_setParameter(const char *const key,const double value){
using tfel::material::ViscoElasticityPlaneStressParametersInitializer;
auto& i = ViscoElasticityPlaneStressParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
ViscoElasticity_PlaneStress_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::ViscoElasticityPlaneStressParametersInitializer;
auto& i = ViscoElasticityPlaneStressParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
ViscoElasticity_setParameter(const char *const key,const double value){
using tfel::material::ViscoElasticityParametersInitializer;
auto& i = ViscoElasticityParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
ViscoElasticity_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::ViscoElasticityParametersInitializer;
auto& i = ViscoElasticityParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int ViscoElasticity_AxisymmetricalGeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRAIN;
using Behaviour = ViscoElasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ViscoElasticity_getOutOfBoundsPolicy());
return r;
} // end of ViscoElasticity_AxisymmetricalGeneralisedPlaneStrain

MFRONT_SHAREDOBJ int ViscoElasticity_AxisymmetricalGeneralisedPlaneStress(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRESS;
using Behaviour = ViscoElasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ViscoElasticity_getOutOfBoundsPolicy());
return r;
} // end of ViscoElasticity_AxisymmetricalGeneralisedPlaneStress

MFRONT_SHAREDOBJ int ViscoElasticity_Axisymmetrical(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICAL;
using Behaviour = ViscoElasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ViscoElasticity_getOutOfBoundsPolicy());
return r;
} // end of ViscoElasticity_Axisymmetrical

MFRONT_SHAREDOBJ int ViscoElasticity_PlaneStress(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::PLANESTRESS;
using Behaviour = ViscoElasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ViscoElasticity_getOutOfBoundsPolicy());
return r;
} // end of ViscoElasticity_PlaneStress

MFRONT_SHAREDOBJ int ViscoElasticity_PlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::PLANESTRAIN;
using Behaviour = ViscoElasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ViscoElasticity_getOutOfBoundsPolicy());
return r;
} // end of ViscoElasticity_PlaneStrain

MFRONT_SHAREDOBJ int ViscoElasticity_GeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::GENERALISEDPLANESTRAIN;
using Behaviour = ViscoElasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ViscoElasticity_getOutOfBoundsPolicy());
return r;
} // end of ViscoElasticity_GeneralisedPlaneStrain

MFRONT_SHAREDOBJ int ViscoElasticity_Tridimensional(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::TRIDIMENSIONAL;
using Behaviour = ViscoElasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ViscoElasticity_getOutOfBoundsPolicy());
return r;
} // end of ViscoElasticity_Tridimensional

#ifdef __cplusplus
}
#endif /* __cplusplus */

