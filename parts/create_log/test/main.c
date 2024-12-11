/*****************************************************************************/
/*
*	filename:main.c
*	about:
*		C code template main file
*		
*	attention:
*		library libschrocat.a is used, include schrocat1.h and schrocat2.h
*
*	history:
*		2024/11/03:K.Yamada :create this file
*/
/*****************************************************************************/
/*****************************************************************************/
/*                         include headerfile                                */
/*****************************************************************************/
/*standard library*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <log.h>

#include <main.h>

/*****************************************************************************/
/*                               define macro                                */
/*****************************************************************************/

/*****************************************************************************/
/*                         define variable (global)                          */
/*****************************************************************************/
/*none*/

/*****************************************************************************/
/*                         define structure (global)                         */
/*****************************************************************************/
/*none*/

/*****************************************************************************/
/*                         define type (global)                              */
/*****************************************************************************/
/*none*/

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
*	out	int64_t				:error code
*/
int64_t main(uint64_t argc, char const* argv[])
{
	int64_t ret = 0;

	INFOMSG("start");
	test_function();

	/*switch compile option (debug code)*/
#ifdef _DEBUG
	printf("DEBUG code\r\n\r\n");
#endif /*_DEBUG*/

	INFOMSG("end");
	return 0;
}
