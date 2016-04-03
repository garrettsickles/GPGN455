#include <math.h>
#include <stdio.h>

#include "stereonet.h"

int main()
{
	double p[2], d[2], l[2];
	double az[3], pl[3];

	printf("Please input the following stereonet values:\n");

	printf("Strike (Phi):\t");
	scanf("%lf", &(p[0]));

	printf("Dip (delta):\t");
	scanf("%lf", &(d[0]));

	printf("Slip (lambda):\t");
	scanf("%lf", &(l[0]));

	p[0] = TO_RADIANS(p[0]);
	d[0] = TO_RADIANS(d[0]);
	l[0] = TO_RADIANS(l[0]);

	get_P_vector(p[0], d[0], l[0], &az[0], &pl[0]);
	get_T_vector(p[0], d[0], l[0], &az[1], &pl[1]);
	get_B_vector(p[0], d[0], l[0], &az[2], &pl[2]);

	get_aux_plane(p[0], d[0], l[0], &p[1], &d[1], &l[1]);

	p[0] = TO_DEGREES(p[0]);
	d[0] = TO_DEGREES(d[0]);
	l[0] = TO_DEGREES(l[0]);
	p[1] = TO_DEGREES(p[1]);
	d[1] = TO_DEGREES(d[1]);
	l[1] = TO_DEGREES(l[1]);
	az[0] = TO_DEGREES(az[0]);
	az[1] = TO_DEGREES(az[1]);
	az[2] = TO_DEGREES(az[2]);
	pl[0] = TO_DEGREES(pl[0]);
	pl[1] = TO_DEGREES(pl[1]);
	pl[2] = TO_DEGREES(pl[2]);

	print_fault(p[0], d[0], l[0], "Fault");
	print_fault(p[1], d[1], l[1], "Auxillary");
	print_vector(az[0], pl[0], "P");
	print_vector(az[1], pl[1], "T");
	print_vector(az[2], pl[2], "B");
	return 0;
}