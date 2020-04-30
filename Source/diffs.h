#ifndef DIFFS_H
#define DIFFS_H

#define PRECALC_LEN 38
#define CACHE_LEN 3

void precalculate(double M, double N, double alpha, double eta_a, double eta_b, double lambda, double * p);

void cache_diff_y_j(double y_b, double y_n, double * p, double * c);

double diff_y_j(double d, double y_j, double * p, double * c);

void cache_diff_y_0(double x2_M_1, double x2_M_2, double y_1, double * p, double * c);

double diff_y_0(double d, double y_0, double * p, double * c);

void cache_diff_y_N_1(double x1_0, double y_N_2, double * p, double * c);

double diff_y_N_1(double d, double y_N_1, double * p, double * c);

void cache_diff_x1_j(double x1_b, double x1_bb, double x1_n, double x1_nn, double * p, double * c);

double diff_x1_j(double d, double x1_j, double * p, double * c);

void cache_diff_x1_0(double x1_1, double x1_2, double y_N_1, double * p, double * c);

double diff_x1_0(double d, double x1_0, double * p, double * c);

void cache_diff_x1_1(double x1_0, double x1_2, double x1_3, double * p, double * c);

double diff_x1_1(double d, double x1_1, double * p, double * c);

void cache_diff_x1_M_2(double x1_M_1, double x1_M_3, double x1_M_4, double x2_0, double * p, double * c);

double diff_x1_M_2(double d, double x1_M_2, double * p, double * c);

void cache_diff_x1_M_1(double x1_M_2, double x1_M_3, double x2_0, double x2_1, double * p, double * c);

double diff_x1_M_1(double d, double x1_M_1, double * p, double * c);

void cache_diff_x2_j(double x2_b, double x2_bb, double x2_n, double x2_nn, double * p, double * c);

double diff_x2_j(double d, double x2_j, double * p, double * c);

void cache_diff_x2_0(double x1_M_1, double x1_M_2, double x2_1, double x2_2, double * p, double * c);

double diff_x2_0(double d, double x2_0, double * p, double * c);

void cache_diff_x2_1(double x1_M_1, double x2_0, double x2_2, double x2_3, double * p, double * c);

double diff_x2_1(double d, double x2_1, double * p, double * c);

void cache_diff_x2_M_2(double x2_M_1, double x2_M_3, double x2_M_4, double y_0, double * p, double * c);

double diff_x2_M_2(double d, double x2_M_2, double * p, double * c);

void cache_diff_x2_M_1(double x2_M_2, double x2_M_3, double y_0, double * p, double * c);

double diff_x2_M_1(double d, double x2_M_1, double * p, double * c);

double observable(double * x1, double * x2, double * y, double lambda, double eta_a, double eta_b, double alpha, int N, int M);

#endif // DIFFS_H
