#include <stdio.h>

double approx_sqrt(double x, double epsilon);

int main()
{
	
	printf("sqrt(%f) = %f\n",14.0, approx_sqrt(14.0, 0.001));
	printf("sqrt(%f) = %f\n",10.0, approx_sqrt(10.0, 0.001));
	printf("sqrt(%f) = %f\n",2.0, approx_sqrt(2.0, 0.001));
	printf("sqrt(%f) = %f\n",100.0, approx_sqrt(100.0, 0.001));
	return 0;
}