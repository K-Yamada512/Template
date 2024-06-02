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
*		2024/04/13:K.Yamada :create this file
*		2024/06/02:K.Yamada :add exercise 4
*/
/*****************************************************************************/
/*****************************************************************************/
/*                         include headerfile                                */
/*****************************************************************************/
/*standard library*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include <source.h>

/*****************************************************************************/
/*                               define const                                */
/*****************************************************************************/
#define  TIME_OUT_LOOP ((uint64_t)100000)

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
double Stirling_formula(uint64_t n){ return (n + 0.5) * log(n) - n + 0.5 * log(2.0 * M_PI); }

static double _exercise_4_1_func(double x){ return x * x * x + 3.0 * x - 1.0; }
static double _exercise_4_1_derivated_func(double x) { return 3.0 * x + 3.0; }
static double _exercise_4_2_func(double x){ return exp(-x) - sin(x); }
static double _exercise_4_2_derivated_func(double x) { return -exp(-x) - cos(x); }
static double _exercise_4_3_func(double x){ return log(log(x)) + x; }
static double _exercise_4_3_derivated_func(double x) { return 1 / (x * log(x)) + 1; }

/*
*	function name:Exercise_1
*	about:
*		calculate summation
*
*		Programming Exercise
*		data type, printf, for, standard library(stdio.h, stdint.h, math.h)
*
*	out	int64_t				:error code
*/
int64_t Exercise_1(void)
{
	int64_t ret = 0;
	uint64_t n_2 = 100;
	uint64_t k_2 = 0;
	uint64_t ans_2_1 = 0;
	double ans_2_2 = 0.0;

	for(uint64_t run_index = 0 ; run_index < n_2 ; run_index++){
		k_2 = run_index + 1;
		ans_2_1 += k_2 + k_2 * k_2 + k_2 * k_2 * k_2;
		ans_2_2 += sin(k_2 * M_PI * sqrt(2)) + cos(k_2 * M_PI * sqrt(3));
	}

	printf("(1) A_n = %10ld (n = %ld)\r\n", ans_2_1, n_2);
	printf("(2) B_n = %10.6lf (n = %ld)\r\n", ans_2_2, n_2);
	printf("\r\n");

	return 0;
}

/*
*	function name:Exercise_2
*	about:
*		calculate Fractrial, Stirling's approximation
*
*		Programming Exercise
*		use header file, if, break, pointer
*
*	out	int64_t				:error code
*/
int64_t Exercise_2(void)
{
	int64_t ret = 0;
	uint64_t n_1 = 0;
	uint64_t ans_1 = 0;
	double left_side = 0.0, right_side = 0.0;

	for(uint64_t run_index = 0 ; run_index < 23 ; run_index++){
		n_1 = run_index + 1;
		ret = Fractrial(&ans_1, n_1);
		printf("n = %3ld, ", n_1);
		if(ret==0){
			left_side = log(ans_1);
			right_side = Stirling_formula(n_1);
			printf("log(n!) = %10.6lf, ", left_side);
			printf("Stirling's formula = %10.6lf, ", right_side);
			printf("Error = %10.6lf\r\n", left_side - right_side);
		}
		else{
			printf("Fractrial Function Error.\r\n");
			break;
		}
	}

	printf("\r\n");

	return 0;
}

/*
*	function name:Exercise_3
*	about:
*		calculate Combination, spherical Bessel function
*
*		Programming Exercise
*		array, recursive function
*
*	out	int64_t				:error code
*/
int64_t Exercise_3(void)
{
	int64_t ret = 0;
	uint64_t n_3 = 0;
	double x_3 = 0;
	uint64_t ans_3 = 0;
	uint64_t ans_array[6];

	printf("(1) Combination\r\n");
	printf("--------------------------------------------------\r\n");
	printf(" n   k = 0   k = 1   k = 2   k = 3   k = 4   k = 5\r\n");
	printf("--------------------------------------------------\r\n");
	for(n_3 = 0; n_3 < 6 ; n_3++){
		ans_array[n_3] = 0;
		printf("%3ld", n_3);
		for(uint64_t run_index = 0; run_index < n_3 + 1 ; run_index++){
			ans_3 = Combination(n_3, run_index);
			ans_array[n_3] += ans_3;
			printf(" %7ld", ans_3);
		}
		printf("\r\n");
	}
	printf("--------------------------------------------------\r\n");
	for(n_3 = 0; n_3 < 6 ; n_3++){
		printf("n = %3ld, sum = %7ld, 2^n = %7.0lf\r\n", n_3, ans_array[n_3], pow(2,n_3));
	}

	printf("(2) spherical Bessel function\r\n");
	printf("---------------------------------------------------------------\r\n");
	printf(" n     x = 1          x = 2          x = 3          x = 4      \r\n");
	printf("---------------------------------------------------------------\r\n");
	for(n_3 = 0; n_3 < 7 ; n_3++){
		printf("%3ld", n_3);
		for(uint64_t run_index = 0; run_index < 4 ; run_index++){
			x_3 = run_index + 1;
			printf(" %+12.11lf", Bessel_func(n_3, x_3));
		}
		printf("\r\n");
	}
	printf("---------------------------------------------------------------\r\n");

	printf("\r\n");

	return 0;
}

/*
*	function name:Exercise_4
*	about:
*		solve f(x) = 0 (method:Bisection, Newton-Raphson)
*
*		Programming Exercise
*		function pointer, structure pointer array, memory allocation
*
*	out	int64_t				:error code
*/
int64_t Exercise_4(void)
{
	int64_t ret = 0;
	double ans_bm = 0;
	uint64_t brk_bm = 0;
	bisection_method_struct bms[3];
	double ans_nr = 0;
	uint64_t brk_nr = 0;
	newton_raphson_method_struct* nrms;

	nrms = (newton_raphson_method_struct *)malloc(sizeof(newton_raphson_method_struct) * 3);

	printf("(1) f(x) = x^3 + 3x - 1\r\n");
	bms[0].p_func = _exercise_4_1_func;
	bms[0].initialization_left = 0.0;
	bms[0].initialization_right = 1.0;
	bms[0].time_out_loop_count = TIME_OUT_LOOP;
	BisectionMethod(&ans_bm, &brk_bm, bms[0]);
	if (brk_bm == TIME_OUT_LOOP){
		printf("Bisection Method      : %.10lf(Break Point : TIMEOUT)\r\n", ans_bm);
	}
	else{
		printf("Bisection Method      : %.10lf(Break Point : %ld)\r\n", ans_bm, brk_bm);
	}

	(nrms)->p_func = _exercise_4_1_func;
	(nrms)->p_derivated_func = _exercise_4_1_derivated_func;
	(nrms)->initialization_x = 0.0;
	(nrms)->time_out_loop_count = TIME_OUT_LOOP;
	NewtonRaphson(&ans_nr, &brk_nr, *(nrms));
	if (brk_nr == TIME_OUT_LOOP){
		printf("Newton-Raphson Method : %.10lf(Break Point : TIMEOUT)\r\n", ans_bm);
	}
	else{
		printf("Newton-Raphson Method : %.10lf(Break Point : %ld)\r\n", ans_bm, brk_nr);
	}


	printf("(2) f(x) = e^-x - sin(x)\r\n");
	bms[1].p_func = _exercise_4_2_func;
	bms[1].initialization_left = 0.0;
	bms[1].initialization_right = 1.0;
	bms[1].time_out_loop_count = TIME_OUT_LOOP;
	BisectionMethod(&ans_bm, &brk_bm, bms[1]);
	if (brk_bm == TIME_OUT_LOOP){
		printf("Bisection Method      : %.10lf(Break Point : TIMEOUT)\r\n", ans_bm);
	}
	else{
		printf("Bisection Method      : %.10lf(Break Point : %ld)\r\n", ans_bm, brk_bm);
	}

	(nrms + 1)->p_func = _exercise_4_2_func;
	(nrms + 1)->p_derivated_func = _exercise_4_2_derivated_func;
	(nrms + 1)->initialization_x = 0.0;
	(nrms + 1)->time_out_loop_count = TIME_OUT_LOOP;
	NewtonRaphson(&ans_nr, &brk_nr, *(nrms + 1));
	if (brk_nr == TIME_OUT_LOOP){
		printf("Newton-Raphson Method : %.10lf(Break Point : TIMEOUT)\r\n", ans_bm);
	}
	else{
		printf("Newton-Raphson Method : %.10lf(Break Point : %ld)\r\n", ans_bm, brk_nr);
	}


	printf("(3) f(x) = ln(ln(x)) + x\r\n");
	bms[2].p_func = _exercise_4_3_func;
	bms[2].initialization_left = 1.2;
	bms[2].initialization_right = 2.0;
	bms[2].time_out_loop_count = TIME_OUT_LOOP;
	BisectionMethod(&ans_bm, &brk_bm, bms[2]);
	if (brk_bm == TIME_OUT_LOOP){
		printf("Bisection Method      : %.10lf(Break Point : TIMEOUT)\r\n", ans_bm);
	}
	else{
		printf("Bisection Method      : %.10lf(Break Point : %ld)\r\n", ans_bm, brk_bm);
	}

	(nrms + 2)->p_func = _exercise_4_3_func;
	(nrms + 2)->p_derivated_func = _exercise_4_3_derivated_func;
	(nrms + 2)->initialization_x = 1.2;
	(nrms + 2)->time_out_loop_count = TIME_OUT_LOOP;
	NewtonRaphson(&ans_nr, &brk_nr, *(nrms + 2));
	if (brk_nr == TIME_OUT_LOOP){
		printf("Newton-Raphson Method : %.10lf(Break Point : TIMEOUT)\r\n", ans_bm);
	}
	else{
		printf("Newton-Raphson Method : %.10lf(Break Point : %ld)\r\n", ans_bm, brk_nr);
	}

	free(nrms);
	
	printf("\r\n");

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
int64_t main(uint64_t argc, char const* argv[])
{
	int64_t ret = 0;

	printf("Programming Exercise Q.1\r\n");
	Exercise_1();

	printf("Programming Exercise Q.2\r\n");
	Exercise_2();

	printf("Programming Exercise Q.3\r\n");
	Exercise_3();

	printf("Programming Exercise Q.4\r\n");
	Exercise_4();

	/*use static library (.a file)*/
	int cat = 0;
	printf("%d\r\n", Nyan(cat));

	int catcat = 0;
	printf("%d\r\n", NyanNyan(catcat));

	Shaaaaaaaa();
	printf("\r\n");

	/*switch compile option (debug code)*/
#ifdef _DEBUG
	printf("DEBUG code\r\n\r\n");
#endif /*_DEBUG*/

	return 0;
}
