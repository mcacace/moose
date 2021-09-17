/*!
* \file   ViscoElasticity-generic.hxx
* \brief  This file declares the umat interface for the ViscoElasticity behaviour law
* \author 
* \date   
*/

#ifndef LIB_GENERIC_VISCOELASTICITY_HXX
#define LIB_GENERIC_VISCOELASTICITY_HXX

#include"TFEL/Config/TFELConfig.hxx"
#include"MFront/GenericBehaviour/BehaviourData.h"

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

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

MFRONT_SHAREDOBJ void
ViscoElasticity_setOutOfBoundsPolicy(const int);

MFRONT_SHAREDOBJ int
ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_setParameter(const char *const,const double);

MFRONT_SHAREDOBJ int
ViscoElasticity_AxisymmetricalGeneralisedPlaneStress_setUnsignedShortParameter(const char *const,const unsigned short);

MFRONT_SHAREDOBJ int
ViscoElasticity_PlaneStress_setParameter(const char *const,const double);

MFRONT_SHAREDOBJ int
ViscoElasticity_PlaneStress_setUnsignedShortParameter(const char *const,const unsigned short);

MFRONT_SHAREDOBJ int
ViscoElasticity_setParameter(const char *const,const double);

MFRONT_SHAREDOBJ int
ViscoElasticity_setUnsignedShortParameter(const char *const,const unsigned short);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int ViscoElasticity_AxisymmetricalGeneralisedPlaneStrain(mfront_gb_BehaviourData* const);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int ViscoElasticity_AxisymmetricalGeneralisedPlaneStress(mfront_gb_BehaviourData* const);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int ViscoElasticity_Axisymmetrical(mfront_gb_BehaviourData* const);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int ViscoElasticity_PlaneStress(mfront_gb_BehaviourData* const);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int ViscoElasticity_PlaneStrain(mfront_gb_BehaviourData* const);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int ViscoElasticity_GeneralisedPlaneStrain(mfront_gb_BehaviourData* const);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int ViscoElasticity_Tridimensional(mfront_gb_BehaviourData* const);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIB_GENERIC_VISCOELASTICITY_HXX */
