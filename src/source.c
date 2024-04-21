/*****************************************************************************/
/*
*	filename:source.c
*	about:
*		C code template main file
*		
*	attention:
*		library libschrocat.a is used, include schrocat1.h and schrocat2.h
*
*	history:
*		2024/04/13:K.Yamada :create file
*/
/*****************************************************************************/
/*****************************************************************************/
/*                         include headerfile                                */
/*****************************************************************************/
//standard library
#include <stdio.h>
#include <stdint.h>

#include <source.h>

/*****************************************************************************/
/*                               define const                                */
/*****************************************************************************/
//none

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
*	function name:main
*	about:
*		project main function
*
*	in	uint64_t	argc	:command line argument number
*	in	char*		argv[]	:command line argument pointer
*	out	int					:error code
*/
int main(uint64_t argc, char const* argv[])
{

	printf("Programming Exercise Q.1\r\n");
	
	int64_t n_1 = 3;
	int64_t ans_1 = 0;
	SumSquare(&ans_1, n_1);

#ifdef _WIN32 //for Windows Visual Studio
	printf("(1) %lld (n = %lld)\r\n", ans_1, n_1);
#else /*_WIN32*/
	printf("(1) %ld (n = %ld)\r\n", ans_1, n_1);
#endif /*_WIN32*/

	int64_t n_2 = 6;
	double ans_2 = 0;
	Basel(&ans_2, n_2);

#ifdef _WIN32 //for Windows Visual Studio
	printf("(2) %.10lf (n = %lld)\r\n", ans_2, n_2);
#else /*_WIN32*/
	printf("(2) %.10lf (n = %ld)\r\n", ans_2, n_2);
#endif /*_WIN32*/

	int cat = 0;
	printf("%d\r\n", Nyan(cat));

	int catcat = 0;
	printf("%d\r\n", NyanNyan(catcat));

	Shaaaaaaaa();

#ifdef _DEBUG
	printf("DEBUG code\r\n");
#endif /*_DEBUG*/

	return 0;
}
