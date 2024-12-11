/*****************************************************************************/
/*
*	filename:calculate.h
*	about:
*		calculate function headerfile
*
*	attention:
*
*	history:
*		2024/12/11:K.Yamada :create this file
*/
/*****************************************************************************/
#ifndef _INCLUDE_GUARD_CALCULATE_H_
#define _INCLUDE_GUARD_CALCULATE_H_

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
typedef struct _bisection_method_structure bisection_method_struct;
typedef struct _newton_raphson_method_structure newton_raphson_method_struct;
typedef struct _runge_kutta_method_structure runge_kutta_method_struct;
typedef struct _equation_of_motion_structure equation_of_motion_struct;

/*****************************************************************************/
/*                                 define function                           */
/*****************************************************************************/

int64_t Fractrial(uint64_t* ans, uint64_t n);

uint64_t Combination(uint64_t n, uint64_t k);

double Bessel_func(uint64_t n, double x);

int64_t BisectionMethod(double* ans, uint64_t* breakpoint, bisection_method_struct bms);

int64_t NewtonRaphson(double* ans, uint64_t* breakpoint, newton_raphson_method_struct nrms);

/*Runge–Kutta method*/
int64_t RungeKutta(double* ans, runge_kutta_method_struct rkms, double t, double x, double cons);

int64_t EOM_for_RungeKutta(double* ans_x, double* ans_v, equation_of_motion_struct eoms);

double EOM_free_fall(double t, double v, double cons);

int64_t EOM_free_fall_exact_solution(double* ans_x, double* ans_v, double initial_x, double initial_v, double t);

double EOM_damped_oscillation(double t, double v, double x);

int64_t EOM_damped_oscillation_exact_solution(double* ans_x, double* ans_v, double initial_x, double initial_v, double t);

#endif /*_INCLUDE_GUARD_CALCULATE_H_*/
