/*****************************************************************************/
/*
*	filename:calculate4.c
*	about:
*		calculate function 4
*
*	attention:
*
*	history:
*		2024/06/03:K.Yamada :create this file
*/
/*****************************************************************************/
/*****************************************************************************/
/*                         include headerfile                                */
/*****************************************************************************/
/*standard library*/
#include <stdlib.h>
#include <stdint.h>

#include <calculate4.h>

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
/*none*/

/*****************************************************************************/
/*                                 define function                           */
/*****************************************************************************/
/*dx/dt = v*/
static double _instantaneous_velocity(double t, double x, double v){ return v; }

/*
*	function name:RungeKutta
*	about:
*		calculate solutions to first-order differential equations by Runge–Kutta method
*
*	out	int64_t*	ans		:calculate answer pointer
*	in	int64_t		n		:order parameter of Runge–Kutta method
*	in	double		delta_t	:time step width
*	in	double		t		:function argument t (time)
*	in	double		v		:function argument v (velocity)
*	out	int64_t				:error code
*/
int64_t RungeKutta(double* ans, runge_kutta_method_struct rkms, double t, double x, double cons)
{
	if (ans == NULL)return -1;
	if (rkms.p_func == NULL)return -1;
	if (rkms.order_para < 1)return -2;

	double k_1 = (*rkms.p_func)(t, x, cons);
	double k_2 = (*rkms.p_func)(t + rkms.delta_t / 2, x + k_1 * rkms.delta_t / 2, cons);
	double k_3 = (*rkms.p_func)(t + rkms.delta_t / 2, x + k_2 * rkms.delta_t / 2, cons);
	double k_4 = (*rkms.p_func)(t + rkms.delta_t, x + k_3 * rkms.delta_t, cons);
	
	if(rkms.order_para == 1)
	{
		*ans = rkms.delta_t * k_1;

	}else if(rkms.order_para == 2)
	{
		*ans = rkms.delta_t * (k_1 + k_2) / 2;

	}else if(rkms.order_para == 3)
	{
		*ans = rkms.delta_t * (k_1 + 4 * k_2 + k_3) / 6;

	}else if(rkms.order_para == 4)
	{
		*ans = rkms.delta_t * (k_1 + 2 * k_2 + 2 * k_3 + k_4) / 6;
	}
	else
	{
		return -3;
	}

	return 0;
}

/*
*	function name:RungeKutta
*	about:
*		calculate solutions to first-order differential equations by Runge–Kutta method
*
*	out	int64_t*	ans		:calculate answer pointer
*	in	int64_t		n		:order parameter of Runge–Kutta method
*	in	double		delta_t	:time step width
*	in	double		t		:function argument t (time)
*	in	double		v		:function argument v (velocity)
*	out	int64_t				:error code
*/
int64_t EOM_for_RungeKutta(double* x_new, double* v_new, equation_of_motion_struct eoms)
{
	if (x_new == NULL)return -1;
	if (v_new == NULL)return -1;
	if (eoms.p_func_v == NULL)return -1;
	if (eoms.order_para < 1)return -2;

	double x_ans = 0.0, v_ans = 0.0;

	runge_kutta_method_struct rkms_x, rkms_v;
	rkms_x.p_func = _instantaneous_velocity;
	rkms_x.delta_t = eoms.delta_t;
	rkms_x.order_para = eoms.order_para;
	rkms_v.p_func = eoms.p_func_v;
	rkms_v.delta_t = eoms.delta_t;
	rkms_v.order_para = eoms.order_para;

	if(RungeKutta(&x_ans, rkms_x, eoms.time, eoms.x_old, eoms.v_old) != 0)
	{
		return -3;
	}
	if(RungeKutta(&v_ans, rkms_v, eoms.time, eoms.v_old, eoms.x_old) != 0)
	{
		return -3;
	}

	*x_new = eoms.x_old + x_ans;
	*v_new = eoms.v_old + v_ans;

	return 0;
}
