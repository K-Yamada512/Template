/*****************************************************************************/
/*
*	filename:calculate.c
*	about:
*		calculate function 1
*
*	attention:
*
*	history:
*		2024/04/13:K.Yamada :create this file
*		2024/12/11:K.Yamada :fix Bessel_func()
*/
/*****************************************************************************/
/*****************************************************************************/
/*                         include headerfile                                */
/*****************************************************************************/
/*standard library*/
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <complex.h>

#include <calculate.h>

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
/*
*	function name:Fractrial
*	about:
*		calculate fractrial (n!)
*
*	out	uint64_t*	ans		:pointer variable to store the answer to the calculation
*	in	uint64_t	n		:natural number
*	out	int64_t				:error code
*/
int64_t Fractrial(uint64_t* ans, uint64_t n)
{
	if (ans == NULL)return -1;
	if (n < 1)return -2;

	*ans = 0;

	uint64_t answer = 1;

	for (uint64_t i = 0; i < n - 1; i++)
	{
		uint64_t n_value = n - i;

		if (n_value >= UINT64_MAX / answer)return -3;
		else answer *= n_value;
	}

	*ans = answer;

	return 0;
}

/*
*	function name:Combination
*	about:
*		calculate combination (nCk)
*
*	in	uint64_t	n		:natural number
*	in	uint64_t	k		:natural number
*	out	uint64_t			:answer to the calculation
*/
uint64_t Combination(uint64_t n, uint64_t k)
{
	if(k == 0) return 1;
	return (n - k + 1.0) / k * Combination(n, k - 1);
}

/*
*	function name:Bessel_func
*	about:
*		calculate spherical Bessel function (j_n(x))
*
*	in	uint64_t	n		:natural number
*	in	double		x		:Arbitrary real number
*	out	double				:answer to the calculation
*/
double Bessel_func(uint64_t n, double x)
{
	if(n == 0){
		if(x == 0) return 1.0;
		return sin(x) / x;
	}
	else if(x == 0) return 0.0;
	else if(n == 1) return sin(x) / (x * x) - cos(x) / x;
	
	return (2.0 * n - 1) * Bessel_func(n - 1, x) / x - Bessel_func(n - 2, x);
}

/*
*	function name:BisectionMethod
*	about:
*		calculate numerical solutions to equations by bisection method
*
*	out	double*						ans			:pointer variable to store the answer to the calculation
*	out	uint64_t*					breakpoint	:pointer variable to store the loop count
*	in	bisection_method_struct		bms			:structure to stores information necessary for bisection method
*	out	int										:error code
*/
int64_t BisectionMethod(double* ans, uint64_t* breakpoint, bisection_method_struct bms)
{
	if (ans == NULL)return -1;
	if (breakpoint == NULL)return -1;
	if (bms.p_func == NULL)return -1;
	*breakpoint = bms.time_out_loop_count;

	double sample_left = bms.initialization_left;
	double sample_right = bms.initialization_right;

	double tmp_left = (*bms.p_func)(sample_left);
	double tmp_right = (*bms.p_func)(sample_right);

	for (int64_t i = 0; i < bms.time_out_loop_count; i++)
	{
		double center = (sample_left + sample_right) / 2.0;

		double value_center = (*bms.p_func)(center);

		if (tmp_left * value_center < 0)sample_right = center;
		else sample_left = center;

		if (sample_left == sample_right)
		{
			*breakpoint = i;
			break;
		}
	}

	double mean_ans = (sample_left + sample_right) / 2.0;

	*ans = mean_ans;

	return 0;
}

/*
*	function name:NewtonRaphson
*	about:
*		calculate numerical solutions to equations by Newton–Raphson method
*
*	out	double*						ans			:pointer variable to store the answer to the calculation
*	out	uint64_t*					breakpoint	:pointer variable to store the loop count
*	in	bisection_method_struct		nrms		:structure to stores information necessary for Newton–Raphson method
*	out	int										:error code
*/
int64_t NewtonRaphson(double* ans, uint64_t* breakpoint, newton_raphson_method_struct nrms)
{
	if (ans == NULL)return -1;
	if (breakpoint == NULL)return -1;
	if (nrms.p_func == NULL)return -1;
	if (nrms.p_derivated_func == NULL)return -1;
	*breakpoint = nrms.time_out_loop_count;

	double ret_ans = nrms.initialization_x;

	for (int64_t i = 0; i < nrms.time_out_loop_count; i++)
	{
		double tmp_ans = ret_ans - (*nrms.p_func)(ret_ans) / (*nrms.p_derivated_func)(ret_ans);

		if (ret_ans == tmp_ans)
		{
			*breakpoint = i;
			break;
		}
		ret_ans = tmp_ans;
	}

	*ans = ret_ans;

	return 0;
}

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

/*
*	function name:EOM_free_fall
*	about:
*		Newton's equation of motion for velocity
*
*	in	double		t		:function argument t (time)
*	in	double		v		:function argument v (velocity)
*	out	double				:return value of function
*/
double EOM_free_fall(double t, double v, double cons)
{
	double m = 1.0, k = 1.0, g = -9.8;

	return g - (k / m) * v;
}

/*
*	function name:EOM_free_fall_exact_solution
*	about:
*		Newton's equation of motion for velocity
*
*	in	double		t		:function argument t (time)
*	in	double		v		:function argument v (velocity)
*	out	double				:return value of function
*/
int64_t EOM_free_fall_exact_solution(double* ans_x, double* ans_v, double initial_x, double initial_v, double t)
{
	if (ans_x == NULL)return -1;
	if (ans_v == NULL)return -1;
	double m = 1.0, k = 1.0, g = -9.8;

	*ans_x = (-m / k) * ((initial_v - g * (m / k)) * (exp(-t * (k / m)) - 1) - g * t) + initial_x;
	*ans_v = (initial_v - g * (m / k)) * exp(-t * (k / m)) + g * (m / k);
	return 0;
}

/*
*	function name:EOM_free_fall
*	about:
*		Newton's equation of motion for velocity
*
*	in	double		t		:function argument t (time)
*	in	double		v		:function argument v (velocity)
*	out	double				:return value of function
*/
double EOM_damped_oscillation(double t, double v, double x)
{
	double omega = 1.0, zeta = 0.5;
	return -2 * zeta * omega * v - omega * omega * x;
}

/*
*	function name:EOM_free_fall
*	about:
*		Newton's equation of motion for velocity
*
*	in	double		t		:function argument t (time)
*	in	double		v		:function argument v (velocity)
*	out	double				:return value of function
*/
int64_t EOM_damped_oscillation_exact_solution(double* ans_x, double* ans_v, double initial_x, double initial_v, double t)
{
	double omega = 1.0, zeta = 0.5;
	double sigma = initial_v / (initial_x * omega);
	double cons_a = initial_x * exp(-zeta * omega * t);

	if(zeta == 1.0)
	{
		*ans_x = cons_a * ((sigma + 1) * omega * t + 1);
		*ans_v = cons_a * (-omega*(((sigma+1)*omega*t+1)+(sigma+1)*omega));
	}
	else
	{
		double _Complex cons_b = csqrt(zeta * zeta - 1);

		*ans_x = creal(cons_a / 2.0 * ((1+((sigma+zeta)/cons_b))*cexp(omega*t*cons_b)+(1-((sigma+zeta)/cons_b))*cexp(-omega*t*cons_b)));
		*ans_v = creal(cons_a / 2.0 * (((-zeta * omega)*((1+((sigma+zeta)/cons_b))*cexp(omega*t*cons_b)+(1-((sigma+zeta)/cons_b))*cexp(-omega*t*cons_b)))+(omega*cons_b)*((1+((sigma+zeta)/cons_b))*cexp(omega*t*cons_b)-(1-((sigma+zeta)/cons_b))*cexp(-omega*t*cons_b))));
	}
	return 0;
}

