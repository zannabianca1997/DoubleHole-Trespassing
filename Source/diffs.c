#include <cmath>
void precalculate(double M, double N, double alpha, double eta_a, double eta_b, double lambda, double * p){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   double t1;
   double t2;
   double t3;
   double t4;
   double t5;
   double t6;
   double t7;
   double t8;
   double t9;
   double t10;
   double t11;
   double t12;
   double t13;
   double t14;
   double t15;
   double t16;
   double t17;
   double t18;
   double t19;
   double t20;
   double t21;
   double t22;
   double t23;
   double t24;
   double t25;
   double t26;
   double t27;
   double t28;
   double t29;
   double t30;
   double t31;
   double t32;
   double t33;
   // Common expressions;
   t0 = 1.0/eta_a;
   t1 = eta_a*eta_a;
   t2 = 2*t1;
   t3 = lambda*lambda;
   t4 = 8*t3;
   t5 = 4*t1;
   t6 = eta_b*eta_b;
   t7 = alpha*t6;
   t8 = lambda*lambda*lambda*lambda;
   t9 = 512*t8;
   t10 = -eta_a*t9 - t4*t7;
   t11 = 1.0/alpha;
   t12 = t11*1.0/t6;
   t13 = t0*t12;
   t14 = 256*t8;
   t15 = -eta_a*t14 - 4*t3*t7;
   t16 = t12*t14;
   t17 = 128*t3;
   t18 = t11*t17;
   t19 = 768*t8;
   t20 = t17*t6;
   t21 = t11*t6;
   t22 = 64*t6;
   t23 = 256*t3;
   t24 = 256*t6;
   t25 = 384*t6;
   t26 = 384*t11*t3;
   t27 = eta_b*eta_b*eta_b*eta_b;
   t28 = 32*t27;
   t29 = -t28;
   t30 = t23*t6;
   t31 = 64*t27;
   t32 = -t31;
   t33 = 512*t3;
   // Calculating output;
   p[0] = -eta_a;
   p[1] = -4*eta_a;
   p[2] = -6*eta_a;
   p[3] = t0*(t2 - t4);
   p[4] = t0*(-16*t3 + t5);
   p[5] = t0*t4;
   p[6] = t13*(t10 + t5*t7);
   p[7] = t13*(t15 + t2*t7);
   p[8] = -t16;
   p[9] = -t18;
   p[10] = t12*(t19 + t20);
   p[11] = -32*t21;
   p[12] = -192*t21;
   p[13] = -480*t21;
   p[14] = t11*(t22 + t23);
   p[15] = -640*t21;
   p[16] = t11*(t24 + 1024*t3);
   p[17] = t11*(t25 + 1536*t3);
   p[18] = -t26;
   p[19] = t12*(-t19 + t29 - t30);
   p[20] = t12*(t32 - t33*t6 - 1536*t8);
   p[21] = t12*(t30 + 1024*t8);
   p[22] = t11*(t17 + t22);
   p[23] = t11*(t24 + t33);
   p[24] = t11*(t25 + 768*t3);
   p[25] = t13*(-eta_a*t20 - eta_a*t28 + t15);
   p[26] = t13*(-eta_a*t30 - eta_a*t31 + t10);
   p[27] = t12*(t19 + t30);
   p[28] = t12*t9;
   p[29] = t11*t24;
   p[30] = t11*t25;
   p[31] = t26;
   p[32] = t12*(t32 - t9);
   p[33] = t11*t22;
   p[34] = t18;
   p[35] = t12*(-t14 + t29);
   p[36] = t12*(t30 + t9);
   p[37] = t16;
}

void cache_diff_y_j(double y_b, double y_n, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   // Common expressions;
   // Calculating output;
   c[0] = (y_b + y_n)*p[5];
}

double diff_y_j(double d, double y_j, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   // Common expressions;
   t0 = d*d;
   // Calculating output;
   return d*y_j*p[4] + d*c[0] + t0*p[2]*(y_j*y_j) + t0*p[3] + p[0]*(d*d*d*d) + p[1]*(d*(y_j*y_j*y_j) + y_j*(d*d*d));
}

void cache_diff_y_0(double x2_M_1, double x2_M_2, double y_1, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   // Common expressions;
   // Calculating output;
   c[0] = x2_M_1*p[10] + x2_M_2*p[8] + y_1*p[5] + p[9]*(x2_M_1*x2_M_1*x2_M_1);
}

double diff_y_0(double d, double y_0, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   // Common expressions;
   t0 = d*d;
   // Calculating output;
   return d*y_0*p[6] + d*c[0] + t0*p[2]*(y_0*y_0) + t0*p[7] + p[0]*(d*d*d*d) + p[1]*(d*(y_0*y_0*y_0) + y_0*(d*d*d));
}

void cache_diff_y_N_1(double x1_0, double y_N_2, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   // Common expressions;
   // Calculating output;
   c[0] = (x1_0 + y_N_2)*p[5];
}

double diff_y_N_1(double d, double y_N_1, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   // Common expressions;
   t0 = d*d;
   // Calculating output;
   return d*y_N_1*p[4] + d*c[0] + t0*p[2]*(y_N_1*y_N_1) + t0*p[3] + p[0]*(d*d*d*d) + p[1]*(d*(y_N_1*y_N_1*y_N_1) + y_N_1*(d*d*d));
}

void cache_diff_x1_j(double x1_b, double x1_bb, double x1_n, double x1_nn, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   // Common expressions;
   t0 = x1_b + x1_n;
   // Calculating output;
   c[0] = t0*p[9];
   c[1] = t0*p[18];
   c[2] = t0*p[21] + (x1_bb + x1_nn)*p[8] + p[9]*(x1_b*x1_b*x1_b + x1_n*x1_n*x1_n);
}

double diff_x1_j(double d, double x1_j, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   double t1;
   double t2;
   double t3;
   double t4;
   // Common expressions;
   t0 = d*d;
   t1 = d*d*d;
   t2 = d*d*d*d;
   t3 = x1_j*x1_j;
   t4 = x1_j*x1_j*x1_j;
   // Calculating output;
   return d*x1_j*p[20] + d*c[2] + t0*t3*p[17] + t0*p[19] + t1*t4*p[15] + t1*c[0] + t2*p[14] + (d*t3 + t0*x1_j)*c[1] + (d*t4 + t1*x1_j)*p[16] + p[11]*(d*d*d*d*d*d) + p[12]*(d*(x1_j*x1_j*x1_j*x1_j*x1_j) + x1_j*(d*d*d*d*d)) + p[13]*(t0*(x1_j*x1_j*x1_j*x1_j) + t2*t3);
}

void cache_diff_x1_0(double x1_1, double x1_2, double y_N_1, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   // Common expressions;
   // Calculating output;
   c[0] = x1_1*p[9];
   c[1] = x1_1*p[18];
   c[2] = x1_1*p[27] + x1_2*p[8] + y_N_1*p[5] + p[9]*(x1_1*x1_1*x1_1);
}

double diff_x1_0(double d, double x1_0, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   double t1;
   double t2;
   double t3;
   double t4;
   // Common expressions;
   t0 = d*d;
   t1 = d*d*d;
   t2 = d*d*d*d;
   t3 = x1_0*x1_0;
   t4 = x1_0*x1_0*x1_0;
   // Calculating output;
   return d*x1_0*p[26] + d*c[2] + t0*t3*p[24] + t0*p[25] + t1*t4*p[15] + t1*c[0] + t2*p[22] + (d*t3 + t0*x1_0)*c[1] + (d*t4 + t1*x1_0)*p[23] + p[11]*(d*d*d*d*d*d) + p[12]*(d*(x1_0*x1_0*x1_0*x1_0*x1_0) + x1_0*(d*d*d*d*d)) + p[13]*(t0*(x1_0*x1_0*x1_0*x1_0) + t2*t3);
}

void cache_diff_x1_1(double x1_0, double x1_2, double x1_3, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   // Common expressions;
   t0 = x1_0 + x1_2;
   // Calculating output;
   c[0] = t0*p[9];
   c[1] = t0*p[18];
   c[2] = x1_0*p[27] + x1_2*p[21] + x1_3*p[8] + p[9]*(x1_0*x1_0*x1_0 + x1_2*x1_2*x1_2);
}

double diff_x1_1(double d, double x1_1, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   double t1;
   double t2;
   double t3;
   double t4;
   // Common expressions;
   t0 = d*d;
   t1 = d*d*d;
   t2 = d*d*d*d;
   t3 = x1_1*x1_1;
   t4 = x1_1*x1_1*x1_1;
   // Calculating output;
   return d*x1_1*p[20] + d*c[2] + t0*t3*p[17] + t0*p[19] + t1*t4*p[15] + t1*c[0] + t2*p[14] + (d*t3 + t0*x1_1)*c[1] + (d*t4 + t1*x1_1)*p[16] + p[11]*(d*d*d*d*d*d) + p[12]*(d*(x1_1*x1_1*x1_1*x1_1*x1_1) + x1_1*(d*d*d*d*d)) + p[13]*(t0*(x1_1*x1_1*x1_1*x1_1) + t2*t3);
}

void cache_diff_x1_M_2(double x1_M_1, double x1_M_3, double x1_M_4, double x2_0, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   // Common expressions;
   t0 = x1_M_1 + x1_M_3;
   // Calculating output;
   c[0] = t0*p[9];
   c[1] = t0*p[18];
   c[2] = t0*p[21] + (x1_M_4 + x2_0)*p[8] + p[9]*(x1_M_1*x1_M_1*x1_M_1 + x1_M_3*x1_M_3*x1_M_3);
}

double diff_x1_M_2(double d, double x1_M_2, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   double t1;
   double t2;
   double t3;
   double t4;
   // Common expressions;
   t0 = d*d;
   t1 = d*d*d;
   t2 = d*d*d*d;
   t3 = x1_M_2*x1_M_2;
   t4 = x1_M_2*x1_M_2*x1_M_2;
   // Calculating output;
   return d*x1_M_2*p[20] + d*c[2] + t0*t3*p[17] + t0*p[19] + t1*t4*p[15] + t1*c[0] + t2*p[14] + (d*t3 + t0*x1_M_2)*c[1] + (d*t4 + t1*x1_M_2)*p[16] + p[11]*(d*d*d*d*d*d) + p[12]*(d*(x1_M_2*x1_M_2*x1_M_2*x1_M_2*x1_M_2) + x1_M_2*(d*d*d*d*d)) + p[13]*(t0*(x1_M_2*x1_M_2*x1_M_2*x1_M_2) + t2*t3);
}

void cache_diff_x1_M_1(double x1_M_2, double x1_M_3, double x2_0, double x2_1, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   // Common expressions;
   t0 = x1_M_2 + x2_0;
   // Calculating output;
   c[0] = t0*p[18];
   c[1] = t0*p[9];
   c[2] = x1_M_2*p[21] + x2_0*p[28] + (x1_M_3 - x2_1)*p[8] + p[9]*(x1_M_2*x1_M_2*x1_M_2 - x2_0*x2_0*x2_0);
}

double diff_x1_M_1(double d, double x1_M_1, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   double t1;
   double t2;
   double t3;
   double t4;
   // Common expressions;
   t0 = d*d;
   t1 = d*d*d;
   t2 = d*d*d*d;
   t3 = x1_M_1*x1_M_1;
   t4 = x1_M_1*x1_M_1*x1_M_1;
   // Calculating output;
   return d*x1_M_1*p[20] + d*c[2] + t0*t3*p[17] + t0*p[19] + t1*t4*p[15] + t1*c[1] + t2*p[14] + (d*t3 + t0*x1_M_1)*c[0] + (d*t4 + t1*x1_M_1)*p[16] + p[11]*(d*d*d*d*d*d) + p[12]*(d*(x1_M_1*x1_M_1*x1_M_1*x1_M_1*x1_M_1) + x1_M_1*(d*d*d*d*d)) + p[13]*(t0*(x1_M_1*x1_M_1*x1_M_1*x1_M_1) + t2*t3);
}

void cache_diff_x2_j(double x2_b, double x2_bb, double x2_n, double x2_nn, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   // Common expressions;
   t0 = x2_b + x2_n;
   // Calculating output;
   c[0] = t0*p[18];
   c[1] = t0*p[9];
   c[2] = t0*p[21] + (x2_bb + x2_nn)*p[8] + p[9]*(x2_b*x2_b*x2_b + x2_n*x2_n*x2_n);
}

double diff_x2_j(double d, double x2_j, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   double t1;
   double t2;
   double t3;
   double t4;
   // Common expressions;
   t0 = d*d;
   t1 = d*d*d;
   t2 = d*d*d*d;
   t3 = x2_j*x2_j;
   t4 = x2_j*x2_j*x2_j;
   // Calculating output;
   return d*x2_j*p[20] + d*c[2] + t0*t3*p[17] + t0*p[19] + t1*t4*p[15] + t1*c[1] + t2*p[14] + (d*t3 + t0*x2_j)*c[0] + (d*t4 + t1*x2_j)*p[16] + p[11]*(d*d*d*d*d*d) + p[12]*(d*(x2_j*x2_j*x2_j*x2_j*x2_j) + x2_j*(d*d*d*d*d)) + p[13]*(t0*(x2_j*x2_j*x2_j*x2_j) + t2*t3);
}

void cache_diff_x2_0(double x1_M_1, double x1_M_2, double x2_1, double x2_2, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   // Common expressions;
   t0 = x1_M_1 - x2_1;
   // Calculating output;
   c[0] = t0*p[31];
   c[1] = t0*p[34];
   c[2] = x1_M_1*p[28] + x2_1*p[36] + (x1_M_2 + x2_2)*p[8] + p[9]*(x1_M_1*x1_M_1*x1_M_1 + x2_1*x2_1*x2_1);
}

double diff_x2_0(double d, double x2_0, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   double t1;
   double t2;
   double t3;
   double t4;
   // Common expressions;
   t0 = d*d;
   t1 = d*d*d;
   t2 = d*d*d*d;
   t3 = x2_0*x2_0;
   t4 = x2_0*x2_0*x2_0;
   // Calculating output;
   return d*x2_0*p[32] + d*c[2] + t0*t3*p[30] + t0*p[35] + t1*t4*p[15] + t1*c[1] + t2*p[33] + (d*t3 + t0*x2_0)*c[0] + (d*t4 + t1*x2_0)*p[29] + p[11]*(d*d*d*d*d*d) + p[12]*(d*(x2_0*x2_0*x2_0*x2_0*x2_0) + x2_0*(d*d*d*d*d)) + p[13]*(t0*(x2_0*x2_0*x2_0*x2_0) + t2*t3);
}

void cache_diff_x2_1(double x1_M_1, double x2_0, double x2_2, double x2_3, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   // Common expressions;
   t0 = x2_0 + x2_2;
   // Calculating output;
   c[0] = t0*p[9];
   c[1] = t0*p[18];
   c[2] = x2_0*p[36] + x2_2*p[21] + (x1_M_1 - x2_3)*p[37] + p[9]*(x2_0*x2_0*x2_0 + x2_2*x2_2*x2_2);
}

double diff_x2_1(double d, double x2_1, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   double t1;
   double t2;
   double t3;
   double t4;
   // Common expressions;
   t0 = d*d;
   t1 = d*d*d;
   t2 = d*d*d*d;
   t3 = x2_1*x2_1;
   t4 = x2_1*x2_1*x2_1;
   // Calculating output;
   return d*x2_1*p[20] + d*c[2] + t0*t3*p[17] + t0*p[19] + t1*t4*p[15] + t1*c[0] + t2*p[14] + (d*t3 + t0*x2_1)*c[1] + (d*t4 + t1*x2_1)*p[16] + p[11]*(d*d*d*d*d*d) + p[12]*(d*(x2_1*x2_1*x2_1*x2_1*x2_1) + x2_1*(d*d*d*d*d)) + p[13]*(t0*(x2_1*x2_1*x2_1*x2_1) + t2*t3);
}

void cache_diff_x2_M_2(double x2_M_1, double x2_M_3, double x2_M_4, double y_0, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   // Common expressions;
   t0 = x2_M_1 + x2_M_3;
   // Calculating output;
   c[0] = t0*p[18];
   c[1] = t0*p[9];
   c[2] = t0*p[21] + (x2_M_4 + y_0)*p[8] + p[9]*(x2_M_1*x2_M_1*x2_M_1 + x2_M_3*x2_M_3*x2_M_3);
}

double diff_x2_M_2(double d, double x2_M_2, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   double t1;
   double t2;
   double t3;
   double t4;
   // Common expressions;
   t0 = d*d;
   t1 = d*d*d;
   t2 = d*d*d*d;
   t3 = x2_M_2*x2_M_2;
   t4 = x2_M_2*x2_M_2*x2_M_2;
   // Calculating output;
   return d*x2_M_2*p[20] + d*c[2] + t0*t3*p[17] + t0*p[19] + t1*t4*p[15] + t1*c[1] + t2*p[14] + (d*t3 + t0*x2_M_2)*c[0] + (d*t4 + t1*x2_M_2)*p[16] + p[11]*(d*d*d*d*d*d) + p[12]*(d*(x2_M_2*x2_M_2*x2_M_2*x2_M_2*x2_M_2) + x2_M_2*(d*d*d*d*d)) + p[13]*(t0*(x2_M_2*x2_M_2*x2_M_2*x2_M_2) + t2*t3);
}

void cache_diff_x2_M_1(double x2_M_2, double x2_M_3, double y_0, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   // Common expressions;
   t0 = x2_M_2 + y_0;
   // Calculating output;
   c[0] = t0*p[9];
   c[1] = t0*p[18];
   c[2] = x2_M_2*p[21] + x2_M_3*p[8] + y_0*p[10] + p[9]*(x2_M_2*x2_M_2*x2_M_2);
}

double diff_x2_M_1(double d, double x2_M_1, double * p, double * c){
   // Automatic generated code;
   // Declaring temp vars;
   double t0;
   double t1;
   double t2;
   double t3;
   double t4;
   // Common expressions;
   t0 = d*d;
   t1 = d*d*d;
   t2 = d*d*d*d;
   t3 = x2_M_1*x2_M_1;
   t4 = x2_M_1*x2_M_1*x2_M_1;
   // Calculating output;
   return d*x2_M_1*p[20] + d*c[2] + t0*t3*p[17] + t0*p[19] + t1*t4*p[15] + t1*c[0] + t2*p[14] + (d*t3 + t0*x2_M_1)*c[1] + (d*t4 + t1*x2_M_1)*p[16] + p[11]*(d*d*d*d*d*d) + p[12]*(d*(x2_M_1*x2_M_1*x2_M_1*x2_M_1*x2_M_1) + x2_M_1*(d*d*d*d*d)) + p[13]*(t0*(x2_M_1*x2_M_1*x2_M_1*x2_M_1) + t2*t3);
}

double observable(double * x1, double * x2, double * y, double lambda, double eta_a, double eta_b, double alpha, int N, int M){
   // Automatic generated code;
   // Declaring temp vars;
   double S0;
   double S1;
   int i;
   double t0;
   double t1;
   double t2;
   double t3;
   double t4;
   double t5;
   double t6;
   double t7;
   double t8;
   double t9;
   double t10;
   double t11;
   // Global common expressions;
   t0 = lambda*lambda;
   t1 = 1.0/eta_b;
   t2 = 4*t1;
   t3 = t0*t2;
   t4 = 4*eta_b;
   t5 = 8*t1;
   t6 = t0*t5;
   t7 = -1 + x2[M - 1]*x2[M - 1];
   t8 = -1 + x1[M - 1]*x1[M - 1];
   t9 = -x1[M - 1] + x2[0];
   t10 = -x2[M - 1] + y[0];
   t11 = t5*t9;
   // Summing S0;
   S0 = 0;
   for (i = 0; i < M - 1; i += 1) {
      S0 += -eta_b*pow(-1 + x1[i]*x1[i], 2) + eta_b*pow(-1 + x2[i]*x2[i], 2) + t3*pow(x1[i + 1] - x1[i], 2) - t3*pow(x2[i + 1] - x2[i], 2);
   };
   // Summing S1;
   S1 = 0;
   for (i = 1; i < M - 1; i += 1) {
      S1 += pow(-t4*x1[i]*(-1 + x1[i]*x1[i]) - t6*(x1[i + 1] - x1[i]) + t6*(-x1[i - 1] + x1[i]), 2) + pow(t4*x2[i]*(-1 + x2[i]*x2[i]) + t6*(x2[i + 1] - x2[i]) - t6*(-x2[i - 1] + x2[i]), 2);
   };
   // Returning output;
   return cos(S0 + eta_b*(t7*t7 - t8*t8) + t0*(-t2*t10*t10 + t2*(t9*t9)))*exp(2*1.0/alpha*(S1 + pow(t0*(-t11 + t5*(x1[M - 1] - x1[M - 2])) - t4*t8*x1[M - 1], 2) + pow(t0*(t10*t5 - t5*(x2[M - 1] - x2[M - 2])) + t4*t7*x2[M - 1], 2) + 16*pow(-2*x2[M - 1] + 2*y[0], 2)*1.0/(eta_b*eta_b)*(lambda*lambda*lambda*lambda) + pow(t0*(t11 + t5*(-x2[0] + x2[1])) + t4*x2[0]*(-1 + x2[0]*x2[0]), 2) + pow(-t4*x1[0]*(-1 + x1[0]*x1[0]) - t6*(-x1[0] + x1[1]), 2)));
}
