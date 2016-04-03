#include <math.h>
#include <stdio.h>

#include "stereonet.h"

void print_fault(double p, double d, double l, const char* name)
{
	printf("\nPlane:      \t%s\n", name);
	printf("Strike (Phi): \t%lf\n", p);
	printf("Dip (delta):  \t%lf\n", d);
	printf("Slip (lambda):\t%lf\n", l);
	return;
}

void print_vector(double az, double pl, const char* name)
{
	printf("\nVector:\t%s\n", name);
	printf("Azimuth: \t%lf\n", az);
	printf("Plunge:  \t%lf\n", pl);
	return;
}

// Find the secondary delta from primary lamda and delta
double Delta2(double delta1, double lamda1)
{
	return acos(sin(lamda1) * sin(delta1));
}

// Find the cosine of the secondary lamda from primary delta and secondary delta
double SinLambda2(double delta1, double delta2)
{
	return cos(delta1)/sin(delta2);
}

// Find the sine of the secondary lamda from primary delta and secondary delta
double CosLambda2(double delta1, double delta2, double lamda1)
{
	return (cos(lamda1)/sin(delta2))*sin(delta1)*(-1.0);
}

double Lambda2(double delta1, double lamda1)
{
	double delta2 = Delta2(delta1, lamda1);
	return atan2(SinLambda2(delta1, delta2), CosLambda2(delta1, delta2, lamda1));
}

double Phi2(double phi1, double delta1, double delta2, double lamda1)
{
	return phi1 - atan2((cos(lamda1)*tan(delta1)),(cos(delta2)*(-1.0)));
}

void get_aux_plane(double p1, double d1, double l1, double* p2, double* d2, double* l2)
{
	*(d2) = Delta2(d1, l1);
	*(l2) = Lambda2(d1, l1);
	*(p2) = Phi2(p1, d1, *(d2), l1);

	if(*(d2) > M_PI/2 && *(d2) < M_PI)
	{
		*(p2) += M_PI;
		*(d2) = M_PI - *(d2);
		*(l2) = 2.0*M_PI - *(l2);
	}

	*(p2) = fmod(*(p2), M_PI*2.0);
	*(l2) = fmod(*(l2), M_PI*2.0);

}

void get_P_vector(double p, double d, double l, double* az, double* pl)
{
	double x = (-1.0)*sin(d)*sin(p)-cos(l)*cos(p)-sin(l)*cos(d)*sin(p);
	double y = (-1.0)*sin(d)*cos(p)+cos(l)*sin(p)-sin(l)*cos(d)*cos(p);
	double z = cos(d)-sin(l)*sin(d);

	*(az) = M_PI - atan2(y,x);
	*(pl) = M_PI/2.0 - atan2(sqrt(x*x+y*y), z);
	if(*(pl) < 0.0) *(az) = fmod(*(az)+M_PI, 2.0*M_PI);
	*(pl) = fabs(*(pl));
}

void get_T_vector(double p, double d, double l, double* az, double* pl)
{
	double x = (-1.0)*sin(d)*sin(p)+cos(l)*cos(p)+sin(l)*cos(d)*sin(p);
	double y = (-1.0)*sin(d)*cos(p)-cos(l)*sin(p)+sin(l)*cos(d)*cos(p);
	double z = cos(d)+sin(l)*sin(d);

	*(az) = M_PI - atan2(y,x);
	*(pl) = M_PI/2.0 - atan2(sqrt(x*x+y*y), z);
	if(*(pl) < 0.0) *(az) = fmod(*(az)+M_PI, 2.0*M_PI);
	*(pl) = fabs(*(pl));
}

void get_B_vector(double p, double d, double l, double* az, double* pl)
{
	double x = (-1.0)*sin(l)*cos(p)+cos(l)*cos(d)*sin(p);
	double y = sin(l)*sin(p)+cos(l)*cos(d)*cos(p);
	double z = cos(l)*sin(d);

	*(az) = M_PI - atan2(y,x);
	*(pl) = M_PI/2.0 - atan2(sqrt(x*x+y*y), z);
	if(*(pl) < 0.0) *(az) = fmod(*(az)+M_PI, 2.0*M_PI);
	*(pl) = fabs(*(pl));
}