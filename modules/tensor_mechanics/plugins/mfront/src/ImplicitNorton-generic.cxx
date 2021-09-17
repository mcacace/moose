/*!
* \file   ImplicitNorton-generic.cxx
* \brief  This file implements the umat interface for the ImplicitNorton behaviour law
* \author Thomas Helfer - modified
* \date   24 / 11 / 2016
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
#include"TFEL/Material/ImplicitNorton.hxx"
#include"MFront/GenericBehaviour/Integrate.hxx"

#include"MFront/GenericBehaviour/ImplicitNorton-generic.hxx"

static tfel::material::OutOfBoundsPolicy&
ImplicitNorton_getOutOfBoundsPolicy(){
using namespace tfel::material;
static OutOfBoundsPolicy policy = None;
return policy;
}

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

MFRONT_SHAREDOBJ const char* 
ImplicitNorton_build_id = "";

MFRONT_SHAREDOBJ const char* 
ImplicitNorton_mfront_ept = "ImplicitNorton";

MFRONT_SHAREDOBJ const char* 
ImplicitNorton_tfel_version = "4.0.0-dev";

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_mfront_mkt = 1u;

MFRONT_SHAREDOBJ const char *
ImplicitNorton_mfront_interface = "Generic";

MFRONT_SHAREDOBJ const char *
ImplicitNorton_src = "ImplicitNorton.mfront";

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_nModellingHypotheses = 7u;

MFRONT_SHAREDOBJ const char * 
ImplicitNorton_ModellingHypotheses[7u] = {"AxisymmetricalGeneralisedPlaneStrain",
"AxisymmetricalGeneralisedPlaneStress",
"Axisymmetrical",
"PlaneStress",
"PlaneStrain",
"GeneralisedPlaneStrain",
"Tridimensional"};

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_nMainVariables = 1;
MFRONT_SHAREDOBJ unsigned short ImplicitNorton_nGradients = 1;

MFRONT_SHAREDOBJ int ImplicitNorton_GradientsTypes[1] = {1};
MFRONT_SHAREDOBJ const char * ImplicitNorton_Gradients[1] = {"Strain"};
MFRONT_SHAREDOBJ unsigned short ImplicitNorton_nThermodynamicForces = 1;

MFRONT_SHAREDOBJ int ImplicitNorton_ThermodynamicForcesTypes[1] = {1};
MFRONT_SHAREDOBJ const char * ImplicitNorton_ThermodynamicForces[1] = {"Stress"};
MFRONT_SHAREDOBJ unsigned short ImplicitNorton_nTangentOperatorBlocks = 2;

MFRONT_SHAREDOBJ const char * ImplicitNorton_TangentOperatorBlocks[2] = {"Stress",
"Strain"};
MFRONT_SHAREDOBJ unsigned short ImplicitNorton_BehaviourType = 1u;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_BehaviourKinematic = 1u;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_SymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_ElasticSymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_api_version = 1u;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_nMaterialProperties = 6u;

MFRONT_SHAREDOBJ const char *ImplicitNorton_MaterialProperties[6u] = {"YoungModulus",
"PoissonRatio",
"ActivationEnthalpy",
"PreExponentialConstant",
"Exponent",
"RConstant"};

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_nInternalStateVariables = 2;
MFRONT_SHAREDOBJ const char * ImplicitNorton_InternalStateVariables[2] = {"ElasticStrain",
"EquivalentViscoplasticStrain"};
MFRONT_SHAREDOBJ int ImplicitNorton_InternalStateVariablesTypes [] = {1,0};

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * ImplicitNorton_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_nParameters = 7;
MFRONT_SHAREDOBJ const char * ImplicitNorton_Parameters[7] = {"RelativeValueForTheEquivalentStressLowerBoundDefinition",
"epsilon","theta","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","numerical_jacobian_epsilon",
"iterMax"};
MFRONT_SHAREDOBJ int ImplicitNorton_ParametersTypes [] = {0,0,0,0,0,0,2};

MFRONT_SHAREDOBJ double ImplicitNorton_RelativeValueForTheEquivalentStressLowerBoundDefinition_ParameterDefaultValue = 1e-12;

MFRONT_SHAREDOBJ double ImplicitNorton_epsilon_ParameterDefaultValue = 1e-16;

MFRONT_SHAREDOBJ double ImplicitNorton_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double ImplicitNorton_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double ImplicitNorton_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double ImplicitNorton_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-17;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short ImplicitNorton_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short ImplicitNorton_nInitializeFunctions= 0;

MFRONT_SHAREDOBJ const char * const * ImplicitNorton_InitializeFunctions = nullptr;


MFRONT_SHAREDOBJ unsigned short ImplicitNorton_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_nMaterialProperties = 6u;

MFRONT_SHAREDOBJ const char *ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_MaterialProperties[6u] = {"YoungModulus",
"PoissonRatio",
"ActivationEnthalpy",
"PreExponentialConstant",
"Exponent",
"RConstant"};

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_nInternalStateVariables = 3;
MFRONT_SHAREDOBJ const char * ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_InternalStateVariables[3] = {"ElasticStrain",
"EquivalentViscoplasticStrain","AxialStrain"};
MFRONT_SHAREDOBJ int ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_InternalStateVariablesTypes [] = {1,0,0};

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_nExternalStateVariables = 1;
MFRONT_SHAREDOBJ const char * ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_ExternalStateVariables[1] = {"AxialStress"};
MFRONT_SHAREDOBJ unsigned short ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_nParameters = 7;
MFRONT_SHAREDOBJ const char * ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_Parameters[7] = {"RelativeValueForTheEquivalentStressLowerBoundDefinition",
"epsilon","theta","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","numerical_jacobian_epsilon",
"iterMax"};
MFRONT_SHAREDOBJ int ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_ParametersTypes [] = {0,0,0,0,0,0,2};

MFRONT_SHAREDOBJ double ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_RelativeValueForTheEquivalentStressLowerBoundDefinition_ParameterDefaultValue = 1e-12;

MFRONT_SHAREDOBJ double ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_epsilon_ParameterDefaultValue = 1e-16;

MFRONT_SHAREDOBJ double ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-17;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_nInitializeFunctions= 0;

MFRONT_SHAREDOBJ const char * const * ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_InitializeFunctions = nullptr;


MFRONT_SHAREDOBJ unsigned short ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_PlaneStress_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_PlaneStress_nMaterialProperties = 6u;

MFRONT_SHAREDOBJ const char *ImplicitNorton_PlaneStress_MaterialProperties[6u] = {"YoungModulus",
"PoissonRatio",
"ActivationEnthalpy",
"PreExponentialConstant",
"Exponent",
"RConstant"};

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_PlaneStress_nInternalStateVariables = 3;
MFRONT_SHAREDOBJ const char * ImplicitNorton_PlaneStress_InternalStateVariables[3] = {"ElasticStrain",
"EquivalentViscoplasticStrain","AxialStrain"};
MFRONT_SHAREDOBJ int ImplicitNorton_PlaneStress_InternalStateVariablesTypes [] = {1,0,0};

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_PlaneStress_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * ImplicitNorton_PlaneStress_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_PlaneStress_nParameters = 7;
MFRONT_SHAREDOBJ const char * ImplicitNorton_PlaneStress_Parameters[7] = {"RelativeValueForTheEquivalentStressLowerBoundDefinition",
"epsilon","theta","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","numerical_jacobian_epsilon",
"iterMax"};
MFRONT_SHAREDOBJ int ImplicitNorton_PlaneStress_ParametersTypes [] = {0,0,0,0,0,0,2};

MFRONT_SHAREDOBJ double ImplicitNorton_PlaneStress_RelativeValueForTheEquivalentStressLowerBoundDefinition_ParameterDefaultValue = 1e-12;

MFRONT_SHAREDOBJ double ImplicitNorton_PlaneStress_epsilon_ParameterDefaultValue = 1e-16;

MFRONT_SHAREDOBJ double ImplicitNorton_PlaneStress_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double ImplicitNorton_PlaneStress_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double ImplicitNorton_PlaneStress_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double ImplicitNorton_PlaneStress_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-17;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_PlaneStress_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_PlaneStress_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short ImplicitNorton_PlaneStress_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short ImplicitNorton_PlaneStress_nInitializeFunctions= 0;

MFRONT_SHAREDOBJ const char * const * ImplicitNorton_PlaneStress_InitializeFunctions = nullptr;


MFRONT_SHAREDOBJ unsigned short ImplicitNorton_PlaneStress_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short ImplicitNorton_PlaneStress_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ void
ImplicitNorton_setOutOfBoundsPolicy(const int p){
if(p==0){
ImplicitNorton_getOutOfBoundsPolicy() = tfel::material::None;
} else if(p==1){
ImplicitNorton_getOutOfBoundsPolicy() = tfel::material::Warning;
} else if(p==2){
ImplicitNorton_getOutOfBoundsPolicy() = tfel::material::Strict;
} else {
std::cerr << "ImplicitNorton_setOutOfBoundsPolicy: invalid argument\n";
}
}

MFRONT_SHAREDOBJ int
ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_setParameter(const char *const key,const double value){
using tfel::material::ImplicitNortonAxisymmetricalGeneralisedPlaneStressParametersInitializer;
auto& i = ImplicitNortonAxisymmetricalGeneralisedPlaneStressParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
ImplicitNorton_AxisymmetricalGeneralisedPlaneStress_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::ImplicitNortonAxisymmetricalGeneralisedPlaneStressParametersInitializer;
auto& i = ImplicitNortonAxisymmetricalGeneralisedPlaneStressParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
ImplicitNorton_PlaneStress_setParameter(const char *const key,const double value){
using tfel::material::ImplicitNortonPlaneStressParametersInitializer;
auto& i = ImplicitNortonPlaneStressParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
ImplicitNorton_PlaneStress_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::ImplicitNortonPlaneStressParametersInitializer;
auto& i = ImplicitNortonPlaneStressParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
ImplicitNorton_setParameter(const char *const key,const double value){
using tfel::material::ImplicitNortonParametersInitializer;
auto& i = ImplicitNortonParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
ImplicitNorton_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::ImplicitNortonParametersInitializer;
auto& i = ImplicitNortonParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int ImplicitNorton_AxisymmetricalGeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRAIN;
using Behaviour = ImplicitNorton<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ImplicitNorton_getOutOfBoundsPolicy());
return r;
} // end of ImplicitNorton_AxisymmetricalGeneralisedPlaneStrain

MFRONT_SHAREDOBJ int ImplicitNorton_AxisymmetricalGeneralisedPlaneStress(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRESS;
using Behaviour = ImplicitNorton<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ImplicitNorton_getOutOfBoundsPolicy());
return r;
} // end of ImplicitNorton_AxisymmetricalGeneralisedPlaneStress

MFRONT_SHAREDOBJ int ImplicitNorton_Axisymmetrical(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICAL;
using Behaviour = ImplicitNorton<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ImplicitNorton_getOutOfBoundsPolicy());
return r;
} // end of ImplicitNorton_Axisymmetrical

MFRONT_SHAREDOBJ int ImplicitNorton_PlaneStress(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::PLANESTRESS;
using Behaviour = ImplicitNorton<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ImplicitNorton_getOutOfBoundsPolicy());
return r;
} // end of ImplicitNorton_PlaneStress

MFRONT_SHAREDOBJ int ImplicitNorton_PlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::PLANESTRAIN;
using Behaviour = ImplicitNorton<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ImplicitNorton_getOutOfBoundsPolicy());
return r;
} // end of ImplicitNorton_PlaneStrain

MFRONT_SHAREDOBJ int ImplicitNorton_GeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::GENERALISEDPLANESTRAIN;
using Behaviour = ImplicitNorton<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ImplicitNorton_getOutOfBoundsPolicy());
return r;
} // end of ImplicitNorton_GeneralisedPlaneStrain

MFRONT_SHAREDOBJ int ImplicitNorton_Tridimensional(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::TRIDIMENSIONAL;
using Behaviour = ImplicitNorton<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ImplicitNorton_getOutOfBoundsPolicy());
return r;
} // end of ImplicitNorton_Tridimensional

#ifdef __cplusplus
}
#endif /* __cplusplus */

