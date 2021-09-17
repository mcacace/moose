/*!
* \file   ViscoPlasticity-generic.hxx
* \brief  This file declares the umat interface for the ViscoPlasticity behaviour law
* \author Mauro Cacace ( GFZ Potsdam )
* \date   
*/

#ifndef LIB_GENERIC_VISCOPLASTICITY_HXX
#define LIB_GENERIC_VISCOPLASTICITY_HXX

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
ViscoPlasticity_setOutOfBoundsPolicy(const int);

MFRONT_SHAREDOBJ int
ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_setParameter(const char *const,const double);

MFRONT_SHAREDOBJ int
ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress_setUnsignedShortParameter(const char *const,const unsigned short);

MFRONT_SHAREDOBJ int
ViscoPlasticity_PlaneStress_setParameter(const char *const,const double);

MFRONT_SHAREDOBJ int
ViscoPlasticity_PlaneStress_setUnsignedShortParameter(const char *const,const unsigned short);

MFRONT_SHAREDOBJ int
ViscoPlasticity_setParameter(const char *const,const double);

MFRONT_SHAREDOBJ int
ViscoPlasticity_setUnsignedShortParameter(const char *const,const unsigned short);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int ViscoPlasticity_AxisymmetricalGeneralisedPlaneStrain(mfront_gb_BehaviourData* const);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int ViscoPlasticity_AxisymmetricalGeneralisedPlaneStress(mfront_gb_BehaviourData* const);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int ViscoPlasticity_Axisymmetrical(mfront_gb_BehaviourData* const);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int ViscoPlasticity_PlaneStress(mfront_gb_BehaviourData* const);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int ViscoPlasticity_PlaneStrain(mfront_gb_BehaviourData* const);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int ViscoPlasticity_GeneralisedPlaneStrain(mfront_gb_BehaviourData* const);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int ViscoPlasticity_Tridimensional(mfront_gb_BehaviourData* const);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIB_GENERIC_VISCOPLASTICITY_HXX */
