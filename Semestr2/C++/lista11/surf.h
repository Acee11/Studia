#ifndef SURF_INCLUDED
#define SURF_INCLUDED
#include <iostream>
#include <math.h>

struct surf
{
	virtual double area( ) const = 0;
	virtual double circumference( ) const = 0;
	virtual surf* clone( ) const & = 0;
	virtual surf* clone( ) && = 0;
	virtual void print( std::ostream& ) const = 0;
	virtual ~surf( ) {};

	static double distance(double x1, double y1, double x2, double y2)
	{
		double a = (x2 - x1);
		double b = (y2 - y1);
		return sqrt(a*a + b*b);
	} 
};

#endif