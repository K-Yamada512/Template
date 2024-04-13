/*****************************************************************************/
/*
*	filename:calculate2.c
*	about:
*		calculate function 2
*
*	attention:
*
*	history:
*		2024/04/13:K.Yamada :create file
*/
/*****************************************************************************/
/*****************************************************************************/
/*                         include headerfile                                */
/*****************************************************************************/
//standard library
#include <stdlib.h>
#include <stdint.h>

#include <calculate2.h>

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
/*
*	function name:Basel
*	about:
*		calculate \prod 1/k^2
*
*	out	int64_t*	ans		:calculate answer pointer
*	in	int64_t		n		:function argument k
*	out	int64_t				:error code
*/
	int64_t Basel(double* ans, int64_t n)
	{
		if (ans == NULL)return -1;
		if (n < 1)return -2;

		*ans = 0;

		double answer = 1.0;

		for (int64_t i = 0; i < n; i++)
		{
			int64_t n_value = n - i;
			double sum_square = 0;

			sum_square = 1.0f / n_value / n_value;

			answer *= sum_square;
		}

		*ans = answer;

		return 0;
	}

#ifdef __cplusplus
}
#endif /*__cplusplus*/
