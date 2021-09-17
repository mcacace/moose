/*!
* \file   ViscoPlasticity-generic.cxx
* \brief  This file implements the umat interface for the ViscoPlasticity behaviour law
* \author Mauro Cacace ( GFZ Potsdam )
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
#include"TFEL/Material/ViscoPlasticity.hxx"
#include"MFront/GenericBehaviour/Integrate.hxx"

#include"MFront/GenericBehaviour/ViscoPlasticity-generic.hxx"

static tfel::material::OutOfBoundsPolicy&
ViscoPlasticity_getOutOfBoundsPolicy(){
using namespace tfel::material;
static OutOfBoundsPolicy policy = None;
return policy;
}

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

MFRONT_SHAREDOBJ const char* 
ViscoPlasticity_build_id = "";

MFRONT_SHAREDOBJ const char* 
ViscoPlasticity_mfront_ept = "ViscoPlasticity";

MFRONT_SHAREDOBJ const char* 
ViscoPlasticity_tfel_version = "4.0.0-dev";

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_mfront_mkt = 1u;

MFRONT_SHAREDOBJ const char *
ViscoPlasticity_mfront_interface = "Generic";

MFRONT_SHAREDOBJ const char *
ViscoPlasticity_src = "ViscoPlasticity.mfront";

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_nModellingHypotheses = 7u;

MFRONT_SHAREDOBJ const char * 
ViscoPlasticity_ModellingHypotheses[7u] = {"AxisymmetricalGeneralisedPlaneStrain",
"AxisymmetricalGeneralisedPlaneStress",
"Axisymmetrical",
"PlaneStress",
"PlaneStrain",
"GeneralisedPlaneStrain",
"Tridimensional"};

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_nMainVariables = 1;
MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_nGradients = 1;

MFRONT_SHAREDOBJ int ViscoPlasticity_GradientsTypes[1] = {1};
MFRONT_SHAREDOBJ const char * ViscoPlasticity_Gradients[1] = {"Strain"};
MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_nThermodynamicForces = 1;

MFRONT_SHAREDOBJ int ViscoPlasticity_ThermodynamicForcesTypes[1] = {1};
MFRONT_SHAREDOBJ const char * ViscoPlasticity_ThermodynamicForces[1] = {"Stress"};
MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_nTangentOperatorBlocks = 2;

MFRONT_SHAREDOBJ const char * ViscoPlasticity_TangentOperatorBlocks[2] = {"Stress",
"Strain"};
MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_BehaviourType = 1u;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_BehaviourKinematic = 1u;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_SymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_ElasticSymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_api_version = 1u;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_nMaterialProperties = 9u;

MFRONT_SHAREDOBJ const char *ViscoPlasticity_MaterialProperties[9u] = {"YoungModulus",
"PoissonRatio",
"ActivationEnthalpy",
"PreExponentialConstant",
"Exponent",
"RConstant",
"Cohesion",
"FrictionAngle",
"DilationAngle"};

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_nInternalStateVariables = 3;
MFRONT_SHAREDOBJ const char * ViscoPlasticity_InternalStateVariables[3] = {"ElasticStrain",
"EquivalentViscoplasticStrain","EquivalentPlasticStrain"};
MFRONT_SHAREDOBJ int ViscoPlasticity_InternalStateVariablesTypes [] = {1,0,0};

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * ViscoPlasticity_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_nParameters = 7;
MFRONT_SHAREDOBJ const char * ViscoPlasticity_Parameters[7] = {"RelativeValueForTheEquivalentStressLowerBoundDefinition",
"epsilon","theta","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","numerical_jacobian_epsilon",
"iterMax"};
MFRONT_SHAREDOBJ int ViscoPlasticity_ParametersTypes [] = {0,0,0,0,0,0,2};

MFRONT_SHAREDOBJ double ViscoPlasticity_RelativeValueForTheEquivalentStressLowerBoundDefinition_ParameterDefaultValue = 1e-12;

MFRONT_SHAREDOBJ double ViscoPlasticity_epsilon_ParameterDefaultValue = 1e-14;

MFRONT_SHAREDOBJ double ViscoPlasticity_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double ViscoPlasticity_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double ViscoPlasticity_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double ViscoPlasticity_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-15;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_nInitializeFunctions= 0;

MFRONT_SHAREDOBJ const char * const * ViscoPlasticity_InitializeFunctions = nullptr;


MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_nMaterialProperties = 9u;

MFRONT_SHAREDOBJ const char *ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_MaterialProperties[9u] = {"YoungModulus",
"PoissonRatio",
"ActivationEnthalpy",
"PreExponentialConstant",
"Exponent",
"RConstant",
"Cohesion",
"FrictionAngle",
"DilationAngle"};

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_nInternalStateVariables = 4;
MFRONT_SHAREDOBJ const char * ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_InternalStateVariables[4] = {"ElasticStrain",
"EquivalentViscoplasticStrain","EquivalentPlasticStrain","AxialStrain"};
MFRONT_SHAREDOBJ int ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_InternalStateVariablesTypes [] = {1,0,0,0};

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_nExternalStateVariables = 1;
MFRONT_SHAREDOBJ const char * ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_ExternalStateVariables[1] = {"AxialStress"};
MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_nParameters = 7;
MFRONT_SHAREDOBJ const char * ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_Parameters[7] = {"RelativeValueForTheEquivalentStressLowerBoundDefinition",
"epsilon","theta","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","numerical_jacobian_epsilon",
"iterMax"};
MFRONT_SHAREDOBJ int ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_ParametersTypes [] = {0,0,0,0,0,0,2};

MFRONT_SHAREDOBJ double ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_RelativeValueForTheEquivalentStressLowerBoundDefinition_ParameterDefaultValue = 1e-12;

MFRONT_SHAREDOBJ double ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_epsilon_ParameterDefaultValue = 1e-14;

MFRONT_SHAREDOBJ double ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-15;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_nInitializeFunctions= 0;

MFRONT_SHAREDOBJ const char * const * ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_InitializeFunctions = nullptr;


MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_PlaneStress_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_PlaneStress_nMaterialProperties = 9u;

MFRONT_SHAREDOBJ const char *ViscoPlasticity_PlaneStress_MaterialProperties[9u] = {"YoungModulus",
"PoissonRatio",
"ActivationEnthalpy",
"PreExponentialConstant",
"Exponent",
"RConstant",
"Cohesion",
"FrictionAngle",
"DilationAngle"};

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_PlaneStress_nInternalStateVariables = 4;
MFRONT_SHAREDOBJ const char * ViscoPlasticity_PlaneStress_InternalStateVariables[4] = {"ElasticStrain",
"EquivalentViscoplasticStrain","EquivalentPlasticStrain","AxialStrain"};
MFRONT_SHAREDOBJ int ViscoPlasticity_PlaneStress_InternalStateVariablesTypes [] = {1,0,0,0};

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_PlaneStress_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * ViscoPlasticity_PlaneStress_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_PlaneStress_nParameters = 7;
MFRONT_SHAREDOBJ const char * ViscoPlasticity_PlaneStress_Parameters[7] = {"RelativeValueForTheEquivalentStressLowerBoundDefinition",
"epsilon","theta","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","numerical_jacobian_epsilon",
"iterMax"};
MFRONT_SHAREDOBJ int ViscoPlasticity_PlaneStress_ParametersTypes [] = {0,0,0,0,0,0,2};

MFRONT_SHAREDOBJ double ViscoPlasticity_PlaneStress_RelativeValueForTheEquivalentStressLowerBoundDefinition_ParameterDefaultValue = 1e-12;

MFRONT_SHAREDOBJ double ViscoPlasticity_PlaneStress_epsilon_ParameterDefaultValue = 1e-14;

MFRONT_SHAREDOBJ double ViscoPlasticity_PlaneStress_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double ViscoPlasticity_PlaneStress_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double ViscoPlasticity_PlaneStress_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double ViscoPlasticity_PlaneStress_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-15;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_PlaneStress_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_PlaneStress_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_PlaneStress_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_PlaneStress_nInitializeFunctions= 0;

MFRONT_SHAREDOBJ const char * const * ViscoPlasticity_PlaneStress_InitializeFunctions = nullptr;


MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_PlaneStress_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short ViscoPlasticity_PlaneStress_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ void
ViscoPlasticity_setOutOfBoundsPolicy(const int p){
if(p==0){
ViscoPlasticity_getOutOfBoundsPolicy() = tfel::material::None;
} else if(p==1){
ViscoPlasticity_getOutOfBoundsPolicy() = tfel::material::Warning;
} else if(p==2){
ViscoPlasticity_getOutOfBoundsPolicy() = tfel::material::Strict;
} else {
std::cerr << "ViscoPlasticity_setOutOfBoundsPolicy: invalid argument\n";
}
}

MFRONT_SHAREDOBJ int
ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_setParameter(const char *const key,const double value){
using tfel::material::ViscoPlasticityAxisymmetricalGeneralisedPlaneStressParametersInitializer;
auto& i = ViscoPlasticityAxisymmetricalGeneralisedPlaneStressParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::ViscoPlasticityAxisymmetricalGeneralisedPlaneStressParametersInitializer;
auto& i = ViscoPlasticityAxisymmetricalGeneralisedPlaneStressParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
ViscoPlasticity_PlaneStress_setParameter(const char *const key,const double value){
using tfel::material::ViscoPlasticityPlaneStressParametersInitializer;
auto& i = ViscoPlasticityPlaneStressParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
ViscoPlasticity_PlaneStress_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::ViscoPlasticityPlaneStressParametersInitializer;
auto& i = ViscoPlasticityPlaneStressParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
ViscoPlasticity_setParameter(const char *const key,const double value){
using tfel::material::ViscoPlasticityParametersInitializer;
auto& i = ViscoPlasticityParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
ViscoPlasticity_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::ViscoPlasticityParametersInitializer;
auto& i = ViscoPlasticityParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int ViscoPlasticity_AxisymmetricalGeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRAIN;
using Behaviour = ViscoPlasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ViscoPlasticity_getOutOfBoundsPolicy());
return r;
} // end of ViscoPlasticity_AxisymmetricalGeneralisedPlaneStrain

MFRONT_SHAREDOBJ int ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRESS;
using Behaviour = ViscoPlasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ViscoPlasticity_getOutOfBoundsPolicy());
return r;
} // end of ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress

MFRONT_SHAREDOBJ int ViscoPlasticity_Axisymmetrical(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICAL;
using Behaviour = ViscoPlasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ViscoPlasticity_getOutOfBoundsPolicy());
return r;
} // end of ViscoPlasticity_Axisymmetrical

MFRONT_SHAREDOBJ int ViscoPlasticity_PlaneStress(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::PLANESTRESS;
using Behaviour = ViscoPlasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ViscoPlasticity_getOutOfBoundsPolicy());
return r;
} // end of ViscoPlasticity_PlaneStress

MFRONT_SHAREDOBJ int ViscoPlasticity_PlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::PLANESTRAIN;
using Behaviour = ViscoPlasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ViscoPlasticity_getOutOfBoundsPolicy());
return r;
} // end of ViscoPlasticity_PlaneStrain

MFRONT_SHAREDOBJ int ViscoPlasticity_GeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::GENERALISEDPLANESTRAIN;
using Behaviour = ViscoPlasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ViscoPlasticity_getOutOfBoundsPolicy());
return r;
} // end of ViscoPlasticity_GeneralisedPlaneStrain

MFRONT_SHAREDOBJ int ViscoPlasticity_Tridimensional(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::TRIDIMENSIONAL;
using Behaviour = ViscoPlasticity<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, ViscoPlasticity_getOutOfBoundsPolicy());
return r;
} // end of ViscoPlasticity_Tridimensional

#ifdef __cplusplus
}
#endif /* __cplusplus */

