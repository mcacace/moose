/*!
* \file   BDT-generic.cxx
* \brief  This file implements the umat interface for the BDT behaviour law
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
#include"TFEL/Material/BDT.hxx"
#include"MFront/GenericBehaviour/Integrate.hxx"

#include"MFront/GenericBehaviour/BDT-generic.hxx"

static tfel::material::OutOfBoundsPolicy&
BDT_getOutOfBoundsPolicy(){
using namespace tfel::material;
static OutOfBoundsPolicy policy = None;
return policy;
}

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

MFRONT_SHAREDOBJ const char* 
BDT_build_id = "";

MFRONT_SHAREDOBJ const char* 
BDT_mfront_ept = "BDT";

MFRONT_SHAREDOBJ const char* 
BDT_tfel_version = "4.0.0-dev";

MFRONT_SHAREDOBJ unsigned short BDT_mfront_mkt = 1u;

MFRONT_SHAREDOBJ const char *
BDT_mfront_interface = "Generic";

MFRONT_SHAREDOBJ const char *
BDT_src = "BDT.mfront";

MFRONT_SHAREDOBJ unsigned short BDT_nModellingHypotheses = 5u;

MFRONT_SHAREDOBJ const char * 
BDT_ModellingHypotheses[5u] = {"AxisymmetricalGeneralisedPlaneStrain",
"Axisymmetrical",
"PlaneStrain",
"GeneralisedPlaneStrain",
"Tridimensional"};

MFRONT_SHAREDOBJ unsigned short BDT_nMainVariables = 1;
MFRONT_SHAREDOBJ unsigned short BDT_nGradients = 1;

MFRONT_SHAREDOBJ int BDT_GradientsTypes[1] = {1};
MFRONT_SHAREDOBJ const char * BDT_Gradients[1] = {"Strain"};
MFRONT_SHAREDOBJ unsigned short BDT_nThermodynamicForces = 1;

MFRONT_SHAREDOBJ int BDT_ThermodynamicForcesTypes[1] = {1};
MFRONT_SHAREDOBJ const char * BDT_ThermodynamicForces[1] = {"Stress"};
MFRONT_SHAREDOBJ unsigned short BDT_nTangentOperatorBlocks = 2;

MFRONT_SHAREDOBJ const char * BDT_TangentOperatorBlocks[2] = {"Stress",
"Strain"};
MFRONT_SHAREDOBJ unsigned short BDT_BehaviourType = 1u;

MFRONT_SHAREDOBJ unsigned short BDT_BehaviourKinematic = 1u;

MFRONT_SHAREDOBJ unsigned short BDT_SymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short BDT_ElasticSymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short BDT_api_version = 1u;

MFRONT_SHAREDOBJ unsigned short BDT_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short BDT_nMaterialProperties = 20u;

MFRONT_SHAREDOBJ const char *BDT_MaterialProperties[20u] = {"YoungModulus",
"PoissonRatio",
"ThermalExpansion",
"f_c",
"m_0",
"alpha_p",
"n_exp_T",
"q_h0",
"chi_h",
"alpha_d",
"h_d",
"Qact",
"A_creep",
"n_creep",
"El_1",
"El_2",
"El_3",
"at_1",
"at_2",
"at_3"};

MFRONT_SHAREDOBJ unsigned short BDT_nInternalStateVariables = 7;
MFRONT_SHAREDOBJ const char * BDT_InternalStateVariables[7] = {"ElasticStrain",
"pla_mult","a","dam","Rv","triax_p",
"vp"};
MFRONT_SHAREDOBJ int BDT_InternalStateVariablesTypes [] = {1,0,0,0,0,0,0};

MFRONT_SHAREDOBJ unsigned short BDT_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * BDT_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short BDT_nParameters = 6;
MFRONT_SHAREDOBJ const char * BDT_Parameters[6] = {"theta",
"minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","epsilon","numerical_jacobian_epsilon","iterMax"};
MFRONT_SHAREDOBJ int BDT_ParametersTypes [] = {0,0,0,0,0,2};

MFRONT_SHAREDOBJ double BDT_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double BDT_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double BDT_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double BDT_epsilon_ParameterDefaultValue = 1e-08;

MFRONT_SHAREDOBJ double BDT_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-09;

MFRONT_SHAREDOBJ unsigned short BDT_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short BDT_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short BDT_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short BDT_nInitializeFunctions= 0;

MFRONT_SHAREDOBJ const char * const * BDT_InitializeFunctions = nullptr;


MFRONT_SHAREDOBJ unsigned short BDT_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short BDT_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ void
BDT_setOutOfBoundsPolicy(const int p){
if(p==0){
BDT_getOutOfBoundsPolicy() = tfel::material::None;
} else if(p==1){
BDT_getOutOfBoundsPolicy() = tfel::material::Warning;
} else if(p==2){
BDT_getOutOfBoundsPolicy() = tfel::material::Strict;
} else {
std::cerr << "BDT_setOutOfBoundsPolicy: invalid argument\n";
}
}

MFRONT_SHAREDOBJ int
BDT_setParameter(const char *const key,const double value){
using tfel::material::BDTParametersInitializer;
auto& i = BDTParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
BDT_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::BDTParametersInitializer;
auto& i = BDTParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int BDT_AxisymmetricalGeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRAIN;
using Behaviour = BDT<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, BDT_getOutOfBoundsPolicy());
return r;
} // end of BDT_AxisymmetricalGeneralisedPlaneStrain

MFRONT_SHAREDOBJ int BDT_Axisymmetrical(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::AXISYMMETRICAL;
using Behaviour = BDT<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, BDT_getOutOfBoundsPolicy());
return r;
} // end of BDT_Axisymmetrical

MFRONT_SHAREDOBJ int BDT_PlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::PLANESTRAIN;
using Behaviour = BDT<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, BDT_getOutOfBoundsPolicy());
return r;
} // end of BDT_PlaneStrain

MFRONT_SHAREDOBJ int BDT_GeneralisedPlaneStrain(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::GENERALISEDPLANESTRAIN;
using Behaviour = BDT<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, BDT_getOutOfBoundsPolicy());
return r;
} // end of BDT_GeneralisedPlaneStrain

MFRONT_SHAREDOBJ int BDT_Tridimensional(mfront_gb_BehaviourData* const d){
using namespace tfel::material;
using real = mfront::gb::real;
constexpr auto h = ModellingHypothesis::TRIDIMENSIONAL;
using Behaviour = BDT<h,real,false>;
const auto r = mfront::gb::integrate<Behaviour>(*d,Behaviour::STANDARDTANGENTOPERATOR, BDT_getOutOfBoundsPolicy());
return r;
} // end of BDT_Tridimensional

#ifdef __cplusplus
}
#endif /* __cplusplus */

