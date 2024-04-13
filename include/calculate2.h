/*****************************************************************************/
/*
*	filename:calculate2.h
*	about:
*		calculate function 2 headerfile
*
*	attention:
*
*	history:
*		2024/04/13:K.Yamada :create file
*/
/*****************************************************************************/
#ifndef _INCLUDE_GUARD_CALCULATE2_H_
#define _INCLUDE_GUARD_CALCULATE2_H_

/*****************************************************************************/
/*                         include headerfile                                */
/*****************************************************************************/
//standard library
#include <stdint.h>

/*****************************************************************************/
/*                               define const                                */
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/*****************************************************************************/
/*                         define variable (global)                          */
/*****************************************************************************/
//none

/*****************************************************************************/
/*                         define structure (global)                         */
/*****************************************************************************/
//none

/*****************************************************************************/
/*                                 define function                           */
/*****************************************************************************/
	// (2) \prod 1/k^2
	int64_t Basel(double* ans, int64_t n);

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*_INCLUDE_GUARD_CALCULATE2_H_*/
