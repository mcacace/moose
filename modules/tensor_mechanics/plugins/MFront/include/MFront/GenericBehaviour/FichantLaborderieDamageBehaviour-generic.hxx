/*!
* \file   FichantLaborderieDamageBehaviour-generic.hxx
* \brief  This file declares the umat interface for the FichantLaborderieDamageBehaviour behaviour law
* \author A . Gangnant , T . Helfer
* \date   7 / 12 / 2019
*/

#ifndef LIB_GENERIC_FICHANTLABORDERIEDAMAGEBEHAVIOUR_HXX
#define LIB_GENERIC_FICHANTLABORDERIEDAMAGEBEHAVIOUR_HXX

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
FichantLaborderieDamageBehaviour_setOutOfBoundsPolicy(const int);

MFRONT_SHAREDOBJ int
FichantLaborderieDamageBehaviour_setParameter(const char *const,const double);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int FichantLaborderieDamageBehaviour_AxisymmetricalGeneralisedPlaneStrain(mfront_gb_BehaviourData* const);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int FichantLaborderieDamageBehaviour_Axisymmetrical(mfront_gb_BehaviourData* const);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int FichantLaborderieDamageBehaviour_PlaneStrain(mfront_gb_BehaviourData* const);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int FichantLaborderieDamageBehaviour_GeneralisedPlaneStrain(mfront_gb_BehaviourData* const);

/*!
 * \param[in,out] d: material data
 */
MFRONT_SHAREDOBJ int FichantLaborderieDamageBehaviour_Tridimensional(mfront_gb_BehaviourData* const);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIB_GENERIC_FICHANTLABORDERIEDAMAGEBEHAVIOUR_HXX */
