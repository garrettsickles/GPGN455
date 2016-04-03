#ifndef __STEREONET_H__
#define __STEREONET_H__

#include <math.h>
#include <stdio.h>

#define TO_RADIANS(X) X*(M_PI/180.0)
#define TO_DEGREES(X) X*(180.0/M_PI)

void print_fault(double p, double d, double l, const char* name);

void print_vector(double az, double pl, const char* name);

// Find the secondary delta from primary lamda and delta
double Delta2(double delta1, double lamda1);

// Find the cosine of the secondary lamda from primary delta and secondary delta
double SinLambda2(double delta1, double delta2);

// Find the sine of the secondary lamda from primary delta and secondary delta
double CosLambda2(double delta1, double delta2, double lamda1);

double Lambda2(double delta1, double lamda1);

double Phi2(double phi1, double delta1, double delta2, double lamda1);

void get_aux_plane(double p1, double d1, double l1, double* p2, double* d2, double* l2);

void get_P_vector(double p, double d, double l, double* az, double* pl);

void get_T_vector(double p, double d, double l, double* az, double* pl);

void get_B_vector(double p, double d, double l, double* az, double* pl);


#endif