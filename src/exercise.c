/*****************************************************************************/
/*
*	filename:exercise.c
*	about:
*		C code template main file
*		
*	attention:
*
*	history:
*		2024/04/13:K.Yamada :create this file
*		2024/06/02:K.Yamada :add exercise 4
*		2024/06/04:K.Yamada :add exercise 5
*		2024/12/11:K.Yamada :output .dat file
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

#include <calculate.h>

#include <exercise.h>

/*****************************************************************************/
/*                               define macro                                */
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
/*                               define type                                 */
/*****************************************************************************/

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

	FILE *fp;
	uint64_t n_2 = 100;
	uint64_t k_2 = 0;
	uint64_t ans_2_1 = 0;
	double ans_2_2 = 0.0;

	for(uint64_t run_index = 0 ; run_index < n_2 ; run_index++){
		k_2 = run_index + 1;
		ans_2_1 += k_2 + k_2 * k_2 + k_2 * k_2 * k_2;
		ans_2_2 += sin(k_2 * M_PI * sqrt(2)) + cos(k_2 * M_PI * sqrt(3));
	}

	if((fp = fopen("./result/Exercise_1_result.txt", "w")) == NULL){
		ret = -1;
		return ret;
	}
	fprintf(fp, "(1) A_n = %10ld (n = %ld)\r\n", ans_2_1, n_2);
	fprintf(fp, "(2) B_n = %10.6lf (n = %ld)\r\n", ans_2_2, n_2);
	fprintf(fp, "\r\n");
	fclose(fp);
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

	FILE *fp, *fp_dat;
	uint64_t n_1 = 0;
	uint64_t ans_1 = 0;
	double left_side = 0.0, right_side = 0.0;

	if((fp = fopen("./result/Exercise_2_result.txt", "w")) == NULL){
		ret = -1;
		return ret;
	}

	if((fp_dat = fopen("./result/Exercise_2_result.dat", "w")) == NULL){
		ret = -1;
		return ret;
	}

	for(uint64_t run_index = 0 ; run_index < 23 ; run_index++){
		n_1 = run_index + 1;
		ret = Fractrial(&ans_1, n_1);

		fprintf(fp, "n = %3ld, ", n_1);

		if(ret==0){
			left_side = log(ans_1);
			right_side = Stirling_formula(n_1);

			fprintf(fp, "log(n!) = %10.6lf, ", left_side);
			fprintf(fp, "Stirling's formula = %10.6lf, ", right_side);
			fprintf(fp, "Error = %10.6lf, ", left_side - right_side);
			fprintf(fp, "\r\n");

			fprintf(fp_dat, " %3ld,", n_1);
			fprintf(fp_dat, " %10.6lf,", left_side);
			fprintf(fp_dat, " %10.6lf,", right_side);
			fprintf(fp_dat, " %10.6lf,", left_side - right_side);
			fprintf(fp_dat, "\r\n");
		}
		else{
			fprintf(fp, "Fractrial Function Error.\r\n");
			break;
		}
	}

	fclose(fp);
	fclose(fp_dat);
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

	FILE *fp, *fp_dat;
	uint64_t n_3 = 0;
	double x_3 = 0;
	uint64_t ans_3 = 0;
	uint64_t ans_array[6];

	if((fp = fopen("./result/Exercise_3_result.txt", "w")) == NULL){
		ret = -1;
		return ret;
	}

	if((fp_dat = fopen("./result/Exercise_3_result.dat", "w")) == NULL){
		ret = -1;
		return ret;
	}

	fprintf(fp, "(1) Combination\r\n");
	fprintf(fp, "--------------------------------------------------\r\n");
	fprintf(fp, " n   k = 0   k = 1   k = 2   k = 3   k = 4   k = 5\r\n");
	fprintf(fp, "--------------------------------------------------\r\n");
	for(n_3 = 0; n_3 < 6 ; n_3++){
		ans_array[n_3] = 0;
		fprintf(fp, "%3ld", n_3);
		for(uint64_t run_index = 0; run_index < n_3 + 1 ; run_index++){
			ans_3 = Combination(n_3, run_index);
			ans_array[n_3] += ans_3;
			fprintf(fp, " %7ld", ans_3);
		}
		fprintf(fp, "\r\n");
	}
	fprintf(fp, "--------------------------------------------------\r\n");
	for(n_3 = 0; n_3 < 6 ; n_3++){
		fprintf(fp, "n = %3ld, sum = %7ld, 2^n = %7.0lf\r\n", n_3, ans_array[n_3], pow(2,n_3));
	}
	fprintf(fp, "\r\n");
	
	fprintf(fp, "(2) spherical Bessel function\r\n");
	fprintf(fp, "------------------------------------------------------------------\r\n");
	fprintf(fp, "   x      n = 1          n = 2          n = 3          n = 4      \r\n");
	fprintf(fp, "------------------------------------------------------------------\r\n");

	for(uint64_t run_index = 0; run_index < 100 ; run_index++){
		x_3 = run_index * 0.1;
		fprintf(fp, "%5.2lf", x_3);
		fprintf(fp_dat, " %5.2lf,", x_3);
		for(n_3 = 0; n_3 < 4 ; n_3++){
			fprintf(fp, " %+12.11lf", Bessel_func(n_3, x_3));
			fprintf(fp_dat, " %+12.11lf,", Bessel_func(n_3, x_3));
		}
		fprintf(fp, "\r\n");
		fprintf(fp_dat, "\r\n");
	}
	fprintf(fp, "------------------------------------------------------------------\r\n");

	fclose(fp);
	fclose(fp_dat);
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

	FILE *fp;
	double ans_bm = 0;
	uint64_t brk_bm = 0;
	bisection_method_struct bms[3];
	double ans_nr = 0;
	uint64_t brk_nr = 0;
	newton_raphson_method_struct* nrms;

	if((nrms = (newton_raphson_method_struct *)malloc(sizeof(newton_raphson_method_struct) * 3)) == NULL){
		ret = -1;
		return ret;
	}

	if((fp = fopen("./result/Exercise_4_result.txt", "w")) == NULL){
		ret = -1;
		return ret;
	}

	fprintf(fp, "(1) f(x) = x^3 + 3x - 1\r\n");
	bms[0].p_func = _exercise_4_1_func;
	bms[0].initialization_left = 0.0;
	bms[0].initialization_right = 1.0;
	bms[0].time_out_loop_count = TIME_OUT_LOOP;
	BisectionMethod(&ans_bm, &brk_bm, bms[0]);
	if (brk_bm == TIME_OUT_LOOP){
		fprintf(fp, "Bisection Method      : %.10lf(Break Point : TIMEOUT)\r\n", ans_bm);
	}
	else{
		fprintf(fp, "Bisection Method      : %.10lf(Break Point : %ld)\r\n", ans_bm, brk_bm);
	}

	(nrms)->p_func = _exercise_4_1_func;
	(nrms)->p_derivated_func = _exercise_4_1_derivated_func;
	(nrms)->initialization_x = 0.0;
	(nrms)->time_out_loop_count = TIME_OUT_LOOP;
	NewtonRaphson(&ans_nr, &brk_nr, *(nrms));
	if (brk_nr == TIME_OUT_LOOP){
		fprintf(fp, "Newton-Raphson Method : %.10lf(Break Point : TIMEOUT)\r\n", ans_bm);
	}
	else{
		fprintf(fp, "Newton-Raphson Method : %.10lf(Break Point : %ld)\r\n", ans_bm, brk_nr);
	}
	fprintf(fp, "\r\n");


	fprintf(fp, "(2) f(x) = e^-x - sin(x)\r\n");
	bms[1].p_func = _exercise_4_2_func;
	bms[1].initialization_left = 0.0;
	bms[1].initialization_right = 1.0;
	bms[1].time_out_loop_count = TIME_OUT_LOOP;
	BisectionMethod(&ans_bm, &brk_bm, bms[1]);
	if (brk_bm == TIME_OUT_LOOP){
		fprintf(fp, "Bisection Method      : %.10lf(Break Point : TIMEOUT)\r\n", ans_bm);
	}
	else{
		fprintf(fp, "Bisection Method      : %.10lf(Break Point : %ld)\r\n", ans_bm, brk_bm);
	}

	(nrms + 1)->p_func = _exercise_4_2_func;
	(nrms + 1)->p_derivated_func = _exercise_4_2_derivated_func;
	(nrms + 1)->initialization_x = 0.0;
	(nrms + 1)->time_out_loop_count = TIME_OUT_LOOP;
	NewtonRaphson(&ans_nr, &brk_nr, *(nrms + 1));
	if (brk_nr == TIME_OUT_LOOP){
		fprintf(fp, "Newton-Raphson Method : %.10lf(Break Point : TIMEOUT)\r\n", ans_bm);
	}
	else{
		fprintf(fp, "Newton-Raphson Method : %.10lf(Break Point : %ld)\r\n", ans_bm, brk_nr);
	}
	fprintf(fp, "\r\n");


	fprintf(fp, "(3) f(x) = ln(ln(x)) + x\r\n");
	bms[2].p_func = _exercise_4_3_func;
	bms[2].initialization_left = 1.2;
	bms[2].initialization_right = 2.0;
	bms[2].time_out_loop_count = TIME_OUT_LOOP;
	BisectionMethod(&ans_bm, &brk_bm, bms[2]);
	if (brk_bm == TIME_OUT_LOOP){
		fprintf(fp, "Bisection Method      : %.10lf(Break Point : TIMEOUT)\r\n", ans_bm);
	}
	else{
		fprintf(fp, "Bisection Method      : %.10lf(Break Point : %ld)\r\n", ans_bm, brk_bm);
	}

	(nrms + 2)->p_func = _exercise_4_3_func;
	(nrms + 2)->p_derivated_func = _exercise_4_3_derivated_func;
	(nrms + 2)->initialization_x = 1.2;
	(nrms + 2)->time_out_loop_count = TIME_OUT_LOOP;
	NewtonRaphson(&ans_nr, &brk_nr, *(nrms + 2));
	if (brk_nr == TIME_OUT_LOOP){
		fprintf(fp, "Newton-Raphson Method : %.10lf(Break Point : TIMEOUT)\r\n", ans_bm);
	}
	else{
		fprintf(fp, "Newton-Raphson Method : %.10lf(Break Point : %ld)\r\n", ans_bm, brk_nr);
	}

	free(nrms);
	
	fclose(fp);
	return 0;
}

/*
*	function name:Exercise_5
*	about:
*		calculate Fractrial, Stirling's approximation
*
*		Programming Exercise
*		use header file, if, break, pointer
*
*	out	int64_t				:error code
*/
int64_t Exercise_5(void)
{
	int64_t ret = 0;

	FILE *fp, *fp_dat;
	double v_new = 0.0, v_old = 0.0, x_new = 0.0, x_old = 0.0;
	double exact_ans_x = 0.0, exact_ans_v = 0.0;
	double delta_t = 0.1, t_max = 10.0;
	equation_of_motion_struct eoms;

	if((fp = fopen("./result/Exercise_5_result.txt", "w")) == NULL){
		ret = -1;
		return ret;
	}

	if((fp_dat = fopen("./result/Exercise_5_1_result.dat", "w")) == NULL){
		ret = -1;
		return ret;
	}

	fprintf(fp, "(1) free fall\r\n");
	x_old = 0.0;
	v_old = 10.0;
	eoms.p_func_v = EOM_free_fall;
	eoms.delta_t = 0.1;
	eoms.order_para = 4;

	fprintf(fp, "--------------------------------------------------------------------------\r\n");
	fprintf(fp, "   t  ,    x(RK4)      ,    v(RK4)      ,    x(exact)    ,    v(exact)    \r\n");
	fprintf(fp, "--------------------------------------------------------------------------\r\n");
	for(int64_t i = 0 ; i < (t_max / delta_t) + delta_t ; i++)
	{
		eoms.time = i * delta_t;
		eoms.x_old = x_old;
		eoms.v_old = v_old;
		if(EOM_for_RungeKutta(&x_new, &v_new, eoms) != 0)
		{
			fprintf(fp, "error\r\n");
			break;
		}
		EOM_free_fall_exact_solution(&exact_ans_x, &exact_ans_v, 0.0, 10.0, i * delta_t);
		fprintf(fp, "%6.3lf, %+15.10lf, %+15.10lf, %+15.10lf, %+15.10lf\r\n", i * delta_t, x_old, v_old, exact_ans_x, exact_ans_v);
		fprintf(fp_dat, "%6.3lf, %+15.10lf, %+15.10lf, %+15.10lf, %+15.10lf\r\n", i * delta_t, x_old, v_old, exact_ans_x, exact_ans_v);

		/*update*/
		x_old = x_new;
		v_old = v_new;
	}
	fclose(fp_dat);
	fprintf(fp, "--------------------------------------------------------------------------\r\n");
	fprintf(fp, "\r\n");

	if((fp_dat = fopen("./result/Exercise_5_2_result.dat", "w")) == NULL){
		ret = -1;
		return ret;
	}

	fprintf(fp, "(2) damped oscillation\r\n");
	x_old = 1.0;
	v_old = 0.0;
	eoms.p_func_v = EOM_damped_oscillation;
	eoms.delta_t = 0.1;
	eoms.order_para = 4;

	fprintf(fp, "--------------------------------------------------------------------------\r\n");
	fprintf(fp, "   t  ,    x(RK4)      ,    v(RK4)      ,    x(exact)    ,    v(exact)    \r\n");
	fprintf(fp, "--------------------------------------------------------------------------\r\n");
	for(int64_t i = 0 ; i < (t_max / delta_t) + delta_t ; i++)
	{
		eoms.time = i * delta_t;
		eoms.x_old = x_old;
		eoms.v_old = v_old;
		if(EOM_for_RungeKutta(&x_new, &v_new, eoms) != 0)
		{
			fprintf(fp, "error\r\n");
			break;
		}
		EOM_damped_oscillation_exact_solution(&exact_ans_x, &exact_ans_v, 1.0, 0.0, i * delta_t);
		fprintf(fp, "%6.3lf, %+15.10lf, %+15.10lf, %+15.10lf, %+15.10lf\r\n", i * delta_t, x_old, v_old, exact_ans_x, exact_ans_v);
		fprintf(fp_dat, "%6.3lf, %+15.10lf, %+15.10lf, %+15.10lf, %+15.10lf\r\n", i * delta_t, x_old, v_old, exact_ans_x, exact_ans_v);

		/*update*/
		x_old = x_new;
		v_old = v_new;
	}
	fprintf(fp, "--------------------------------------------------------------------------\r\n");

	fclose(fp_dat);
	fclose(fp);

	return 0;
}
