/*****************************************************************************/
/*
*	filename:calculate4.h
*	about:
*		calculate function 4 headerfile
*
*	attention:
*
*	history:
*		2024/06/03:K.Yamada :create this file
*/
/*****************************************************************************/
#ifndef _INCLUDE_GUARD_CALCULATE4_H_
#define _INCLUDE_GUARD_CALCULATE4_H_

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
struct _runge_kutta_method_structure
{
	/*dx/dt = f(t, x(t), const(t))*/
	double (*p_func)(double, double, double); //t, x(t), const(t)
	double delta_t;
	uint64_t order_para;
};

struct _equation_of_motion_structure
{
	/*dv/dt = f(t, v(t), x(t))*/
	double (*p_func_v)(double, double, double); //t, v(t), x(t)
	double delta_t;
	uint64_t order_para;
	double time;
	double x_old;
	double v_old;
};

/*****************************************************************************/
/*                               define type                                 */
/*****************************************************************************/
typedef struct _runge_kutta_method_structure runge_kutta_method_struct;
typedef struct _equation_of_motion_structure equation_of_motion_struct;

/*****************************************************************************/
/*                                 define function                           */
/*****************************************************************************/
/*Runge–Kutta method*/
int64_t RungeKutta(double* ans, runge_kutta_method_struct rkms, double t, double x, double cons);

int64_t EOM_for_RungeKutta(double* ans_x, double* ans_v, equation_of_motion_struct eoms);

#endif /*_INCLUDE_GUARD_CALCULATE4_H_*/
