/*****************************************************************************/
/*
*	filename:calculate1.c
*	about:
*		calculate function 1
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

#include <calculate1.h>

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
*	function name:SumSquare
*	about:
*		calculate \sum k^2
*
*	out	int64_t*	ans		:calculate answer pointer
*	in	int64_t		n		:function argument k
*	out	int64_t				:error code
*/
	int64_t SumSquare(int64_t* ans, int64_t n)
	{
		if (ans == NULL)return -1;
		if (n < 1)return -2;

		*ans = 0;

		int64_t answer = 0;

		for (int64_t i = 0; i < n; i++)
		{
			int64_t n_value = n - i;
			int64_t sum_square = 0;

			if (n_value >= INT64_MAX / n_value)return -3;
			else sum_square = n_value * n_value;

			if (sum_square >= INT64_MAX - answer)return -3;
			else answer += sum_square;
		}

		*ans = answer;

		return 0;
	}

#ifdef __cplusplus
}
#endif /*__cplusplus*/
