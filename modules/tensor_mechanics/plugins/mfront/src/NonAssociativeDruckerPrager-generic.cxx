/*!
* \file   NonAssociativeDruckerPrager-generic.cxx
* \brief  This file implements the umat interface for the NonAssociativeDruckerPrager behaviour law
* \author Thomas Helfer ( modified by Caiua )
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
#include"TFEL/Material/NonAssociativeDruckerPrager.hxx"
#include"MFront/GenericBehaviour/Integrate.hxx"

#include"MFront/GenericBehaviour/NonAssociativeDruckerPrager-generic.hxx"

static tfel::material::OutOfBoundsPolicy&
NonAssociativeDruckerPrager_getOutOfBoundsPolicy(){
using namespace tfel::material;
static OutOfBoundsPolicy policy = None;
return policy;
}

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

MFRONT_SHAREDOBJ const char* 
NonAssociativeDruckerPrager_build_id = "";

MFRONT_SHAREDOBJ const char* 
NonAssociativeDruckerPrager_mfront_ept = "NonAssociativeDruckerPrager";

MFRONT_SHAREDOBJ const char* 
NonAssociativeDruckerPrager_tfel_version = "4.0.0-dev";

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_mfront_mkt = 1u;

MFRONT_SHAREDOBJ const char *
NonAssociativeDruckerPrager_mfront_interface = "Generic";

MFRONT_SHAREDOBJ const char *
NonAssociativeDruckerPrager_src = "NonAssociativeDruckerPrager.mfront";

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_nModellingHypotheses = 7u;

MFRONT_SHAREDOBJ const char * 
NonAssociativeDruckerPrager_ModellingHypotheses[7u] = {"AxisymmetricalGeneralisedPlaneStrain",
"AxisymmetricalGeneralisedPlaneStress",
"Axisymmetrical",
"PlaneStress",
"PlaneStrain",
"GeneralisedPlaneStrain",
"Tridimensional"};

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_nMainVariables = 1;
MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_nGradients = 1;

MFRONT_SHAREDOBJ int NonAssociativeDruckerPrager_GradientsTypes[1] = {1};
MFRONT_SHAREDOBJ const char * NonAssociativeDruckerPrager_Gradients[1] = {"Strain"};
MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_nThermodynamicForces = 1;

MFRONT_SHAREDOBJ int NonAssociativeDruckerPrager_ThermodynamicForcesTypes[1] = {1};
MFRONT_SHAREDOBJ const char * NonAssociativeDruckerPrager_ThermodynamicForces[1] = {"Stress"};
MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_nTangentOperatorBlocks = 2;

MFRONT_SHAREDOBJ const char * NonAssociativeDruckerPrager_TangentOperatorBlocks[2] = {"Stress",
"Strain"};
MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_BehaviourType = 1u;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_BehaviourKinematic = 1u;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_SymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_ElasticSymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_api_version = 1u;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_nMaterialProperties = 5u;

MFRONT_SHAREDOBJ const char *NonAssociativeDruckerPrager_MaterialProperties[5u] = {"YoungModulus",
"PoissonRatio",
"d",
"beta",
"phi"};

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_nInternalStateVariables = 2;
MFRONT_SHAREDOBJ const char * NonAssociativeDruckerPrager_InternalStateVariables[2] = {"ElasticStrain",
"EquivalentPlasticStrain"};
MFRONT_SHAREDOBJ int NonAssociativeDruckerPrager_InternalStateVariablesTypes [] = {1,0};

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * NonAssociativeDruckerPrager_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_nParameters = 7;
MFRONT_SHAREDOBJ const char * NonAssociativeDruckerPrager_Parameters[7] = {"RelativeValueForTheEquivalentStressLowerBoundDefinition",
"epsilon","theta","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","numerical_jacobian_epsilon",
"iterMax"};
MFRONT_SHAREDOBJ int NonAssociativeDruckerPrager_ParametersTypes [] = {0,0,0,0,0,0,2};

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_RelativeValueForTheEquivalentStressLowerBoundDefinition_ParameterDefaultValue = 1e-12;

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_epsilon_ParameterDefaultValue = 1e-16;

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-17;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_nInitializeFunctions= 0;

MFRONT_SHAREDOBJ const char * const * NonAssociativeDruckerPrager_InitializeFunctions = nullptr;


MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_nMaterialProperties = 5u;

MFRONT_SHAREDOBJ const char *NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_MaterialProperties[5u] = {"YoungModulus",
"PoissonRatio",
"d",
"beta",
"phi"};

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_nInternalStateVariables = 3;
MFRONT_SHAREDOBJ const char * NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_InternalStateVariables[3] = {"ElasticStrain",
"EquivalentPlasticStrain","AxialStrain"};
MFRONT_SHAREDOBJ int NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_InternalStateVariablesTypes [] = {1,0,0};

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_nExternalStateVariables = 1;
MFRONT_SHAREDOBJ const char * NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_ExternalStateVariables[1] = {"AxialStress"};
MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_nParameters = 7;
MFRONT_SHAREDOBJ const char * NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_Parameters[7] = {"RelativeValueForTheEquivalentStressLowerBoundDefinition",
"epsilon","theta","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","numerical_jacobian_epsilon",
"iterMax"};
MFRONT_SHAREDOBJ int NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_ParametersTypes [] = {0,0,0,0,0,0,2};

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_RelativeValueForTheEquivalentStressLowerBoundDefinition_ParameterDefaultValue = 1e-12;

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_epsilon_ParameterDefaultValue = 1e-16;

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-17;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_nInitializeFunctions= 0;

MFRONT_SHAREDOBJ const char * const * NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_InitializeFunctions = nullptr;


MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_PlaneStress_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_PlaneStress_nMaterialProperties = 5u;

MFRONT_SHAREDOBJ const char *NonAssociativeDruckerPrager_PlaneStress_MaterialProperties[5u] = {"YoungModulus",
"PoissonRatio",
"d",
"beta",
"phi"};

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_PlaneStress_nInternalStateVariables = 3;
MFRONT_SHAREDOBJ const char * NonAssociativeDruckerPrager_PlaneStress_InternalStateVariables[3] = {"ElasticStrain",
"EquivalentPlasticStrain","AxialStrain"};
MFRONT_SHAREDOBJ int NonAssociativeDruckerPrager_PlaneStress_InternalStateVariablesTypes [] = {1,0,0};

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_PlaneStress_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * NonAssociativeDruckerPrager_PlaneStress_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_PlaneStress_nParameters = 7;
MFRONT_SHAREDOBJ const char * NonAssociativeDruckerPrager_PlaneStress_Parameters[7] = {"RelativeValueForTheEquivalentStressLowerBoundDefinition",
"epsilon","theta","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","numerical_jacobian_epsilon",
"iterMax"};
MFRONT_SHAREDOBJ int NonAssociativeDruckerPrager_PlaneStress_ParametersTypes [] = {0,0,0,0,0,0,2};

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_PlaneStress_RelativeValueForTheEquivalentStressLowerBoundDefinition_ParameterDefaultValue = 1e-12;

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_PlaneStress_epsilon_ParameterDefaultValue = 1e-16;

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_PlaneStress_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_PlaneStress_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_PlaneStress_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double NonAssociativeDruckerPrager_PlaneStress_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-17;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_PlaneStress_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_PlaneStress_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_PlaneStress_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_PlaneStress_nInitializeFunctions= 0;

MFRONT_SHAREDOBJ const char * const * NonAssociativeDruckerPrager_PlaneStress_InitializeFunctions = nullptr;


MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_PlaneStress_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short NonAssociativeDruckerPrager_PlaneStress_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ void
NonAssociativeDruckerPrager_setOutOfBoundsPolicy(const int p){
if(p==0){
NonAssociativeDruckerPrager_getOutOfBoundsPolicy() = tfel::material::None;
} else if(p==1){
NonAssociativeDruckerPrager_getOutOfBoundsPolicy() = tfel::material::Warning;
} else if(p==2){
NonAssociativeDruckerPrager_getOutOfBoundsPolicy() = tfel::material::Strict;
} else {
std::cerr << "NonAssociativeDruckerPrager_setOutOfBoundsPolicy: invalid argument\n";
}
}

MFRONT_SHAREDOBJ int
NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_setParameter(const char *const key,const double value){
using tfel::material::NonAssociativeDruckerPragerAxisymmetricalGeneralisedPlaneStressParametersInitializer;
auto& i = NonAssociativeDruckerPragerAxisymmetricalGeneralisedPlaneStressParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::NonAssociativeDruckerPragerAxisymmetricalGeneralisedPlaneStressParametersInitializer;
auto& i = NonAssociativeDruckerPragerAxisymmetricalGeneralisedPlaneStressParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
NonAssociativeDruckerPrager_PlaneStress_setParameter(const char *const key,const double value){
using tfel::material::NonAssociativeDruckerPragerPlaneStressParametersInitializer;
auto& i = NonAssociativeDruckerPragerPlaneStressParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
NonAssociativeDruckerPrager_PlaneStress_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::NonAssociativeDruckerPragerPlaneStressParametersInitializer;
auto& i = NonAssociativeDruckerPragerPlaneStressParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
NonAssociativeDruckerPrager_setParameter(const char *const key,const double value){
using tfel::material::NonAssociativeDruckerPragerParametersInitializer;
auto& i = NonAssociativeDruckerPragerParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
NonAssociativeDruckerPrager_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::NonAssociativeDruckerPragerParametersInitializer;
auto& i = NonAssociativeDruckerPragerParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRAIN;
using Behaviour = NonAssociativeDruckerPrager<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, NonAssociativeDruckerPrager_getOutOfBoundsPolicy());
return r;
} // end of NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStrain

MFRONT_SHAREDOBJ int NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRESS;
using Behaviour = NonAssociativeDruckerPrager<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, NonAssociativeDruckerPrager_getOutOfBoundsPolicy());
return r;
} // end of NonAssociativeDruckerPrager_AxisymmetricalGeneralisedPlaneStress

MFRONT_SHAREDOBJ int NonAssociativeDruckerPrager_Axisymmetrical(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICAL;
using Behaviour = NonAssociativeDruckerPrager<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, NonAssociativeDruckerPrager_getOutOfBoundsPolicy());
return r;
} // end of NonAssociativeDruckerPrager_Axisymmetrical

MFRONT_SHAREDOBJ int NonAssociativeDruckerPrager_PlaneStress(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::PLANESTRESS;
using Behaviour = NonAssociativeDruckerPrager<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, NonAssociativeDruckerPrager_getOutOfBoundsPolicy());
return r;
} // end of NonAssociativeDruckerPrager_PlaneStress

MFRONT_SHAREDOBJ int NonAssociativeDruckerPrager_PlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::PLANESTRAIN;
using Behaviour = NonAssociativeDruckerPrager<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, NonAssociativeDruckerPrager_getOutOfBoundsPolicy());
return r;
} // end of NonAssociativeDruckerPrager_PlaneStrain

MFRONT_SHAREDOBJ int NonAssociativeDruckerPrager_GeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::GENERALISEDPLANESTRAIN;
using Behaviour = NonAssociativeDruckerPrager<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, NonAssociativeDruckerPrager_getOutOfBoundsPolicy());
return r;
} // end of NonAssociativeDruckerPrager_GeneralisedPlaneStrain

MFRONT_SHAREDOBJ int NonAssociativeDruckerPrager_Tridimensional(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::TRIDIMENSIONAL;
using Behaviour = NonAssociativeDruckerPrager<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, NonAssociativeDruckerPrager_getOutOfBoundsPolicy());
return r;
} // end of NonAssociativeDruckerPrager_Tridimensional

#ifdef __cplusplus
}
#endif /* __cplusplus */

