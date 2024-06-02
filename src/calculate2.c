/*****************************************************************************/
/*
*	filename:calculate2.c
*	about:
*		calculate function 2
*
*	attention:
*
*	history:
*		2024/04/13:K.Yamada :create this file
*		2024/06/02:K.Yamada :create function (Combination, Bessel_func)
*/
/*****************************************************************************/
/*****************************************************************************/
/*                         include headerfile                                */
/*****************************************************************************/
/*standard library*/
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include <calculate2.h>

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
	if(n == 0) return sin(x) / x;
	else if(n == 1) return sin(x) / (x * x) - cos(x) / x;
	
	return (2.0 * n - 1) * Bessel_func(n - 1, x) / x - Bessel_func(n - 2, x);
}
