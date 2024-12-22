/*****************************************************************************/
/*
*	filename:main.c
*	about:
*		C code template main file
*		
*	attention:
*		library libclog.a is used, include log.h
*
*	history:
*		2024/04/13:K.Yamada :create this file
*/
/*****************************************************************************/
/*****************************************************************************/
/*                         include headerfile                                */
/*****************************************************************************/
/*standard library*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*libclog.a*/
#include <log.h>

#include <exercise.h>

#include <main.h>

/*****************************************************************************/
/*                               define macro                                */
/*****************************************************************************/
/*none*/

/*****************************************************************************/
/*                         define variable (global)                          */
/*****************************************************************************/
/*none*/

/*****************************************************************************/
/*                         define structure (global)                         */
/*****************************************************************************/
struct _latice_structure
{
	double x_min;
	double x_max;
	uint64_t x_num;
	double** x_position;
	double y_min;
	double y_max;
	uint64_t y_num;
	double** y_position;
};

/*****************************************************************************/
/*                               define type                                 */
/*****************************************************************************/
typedef struct _latice_structure latice_struct;

/*****************************************************************************/
/*                                 define function                           */
/*****************************************************************************/
/*
*	function name:EOM_free_fall
*	about:
*		Newton's equation of motion for velocity
*
*	in	double		t		:function argument t (time)
*	in	double		v		:function argument v (velocity)
*	out	double				:return value of function
*/
int64_t test2(double* ans, double t, double v, uint64_t count_len, double* const p_const, double b[], double* c)
{
	if (ans == NULL)return -1;
	if (count_len != 3)return -2;
	
	double m = 1.0, g = -9.8, k = 1.0;
	m = p_const[0];
	g = p_const[1];
	k = p_const[2];

	printf("%lf, %lf\r\n", b[1], c[1]);
	b[1] += 1.0;
	printf("%lf, %lf\r\n", b[1], c[1]);

	*ans = g - (k / m) * v;

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
int64_t test(double a[], double b[])
{
	return 0;
}

/*
*	function name:main
*	about:
*		project main function
*
*	in	uint64_t	argc	:command line argument number
*	in	char*		argv[]	:command line argument pointer
*	out	int64_t				:error code
*/
int main(int argc, char const* argv[])
{
	INFOMSG("start");
	int ret = 0;

	double ans = 0.0;
	double a[] = {1.0, -9.8, 1.0};
	double b[] = {0.0, 1.0, 2.0};
	double *c;
	double* const p_a = a;
	const double* p_b = a;
	const double* const p_c = a;
	// p_a = b; //bad (compile error)
	// p_a[0] = 1.0;
	// p_b = b;
	// p_b[0] = 1.0; //bad (compile error)
	// p_c = b; //bad (compile error)
	// p_c[0] = 1.0; //bad (compile error)

	if((c = (double *)malloc(sizeof(double) * 3)) == NULL){
		ret = -1;
		return ret;
	}
	test2(&ans, 0.0, 0.0, 3, p_a, c, c);
	printf("%lf\r\n", c[1]);
	c[1] += 1.0;
	printf("%lf\r\n", c[1]);
	if(c != NULL){
		free(c);
		c = NULL;
	}

	printf("Programming Exercise Q.1\r\n");
	Exercise_1();

	printf("Programming Exercise Q.2\r\n");
	Exercise_2();

	printf("Programming Exercise Q.3\r\n");
	Exercise_3();

	printf("Programming Exercise Q.4\r\n");
	Exercise_4();

	printf("Programming Exercise Q.5\r\n");
	Exercise_5();

	/*switch compile option (debug code)*/
#ifdef _DEBUG
	printf("DEBUG code\r\n\r\n");
#endif /*_DEBUG*/

	INFOMSG("end");
	return 0;
}
