/*****************************************************************************/
/*
*	filename:calculate3.c
*	about:
*		calculate function 3
*
*	attention:
*
*	history:
*		2024/06/02:K.Yamada :create this file
*/
/*****************************************************************************/
/*****************************************************************************/
/*                         include headerfile                                */
/*****************************************************************************/
/*standard library*/
#include <stdlib.h>
#include <stdint.h>

#include <calculate3.h>

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
*	function name:BisectionMethod
*	about:
*		calculate  numerical solutions to equations by bisection method
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
*		calculate  numerical solutions to equations by Newton–Raphson method
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
