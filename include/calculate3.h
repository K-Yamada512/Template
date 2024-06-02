/*****************************************************************************/
/*
*	filename:calculate3.h
*	about:
*		calculate function 3 headerfile
*
*	attention:
*
*	history:
*		2024/06/02:K.Yamada :create this file
*/
/*****************************************************************************/
#ifndef _INCLUDE_GUARD_CALCULATE3_H_
#define _INCLUDE_GUARD_CALCULATE3_H_

/*****************************************************************************/
/*                         include headerfile                                */
/*****************************************************************************/
/*standard library*/
#include <stdint.h>

/*****************************************************************************/
/*                               define const                                */
/*****************************************************************************/
/*none*/

/*****************************************************************************/
/*                         define variable (global)                          */
/*****************************************************************************/
/*none*/

/*****************************************************************************/
/*                         define structure (global)                         */
/*****************************************************************************/
struct _bisection_method_structure
{
	double (*p_func)(double);
	double initialization_left;
	double initialization_right;
	uint64_t time_out_loop_count;
};

struct _newton_raphson_method_structure
{
	double (*p_func)(double);
	double (*p_derivated_func)(double);
	double initialization_x;
	uint64_t time_out_loop_count;
};

/*****************************************************************************/
/*                               define type                                 */
/*****************************************************************************/
typedef struct _bisection_method_structure bisection_method_struct;
typedef struct _newton_raphson_method_structure newton_raphson_method_struct;

/*****************************************************************************/
/*                                 define function                           */
/*****************************************************************************/

int64_t BisectionMethod(double* ans, uint64_t* breakpoint, bisection_method_struct bms);

int64_t NewtonRaphson(double* ans, uint64_t* breakpoint, newton_raphson_method_struct nrms);

#endif /*_INCLUDE_GUARD_CALCULATE3_H_*/
