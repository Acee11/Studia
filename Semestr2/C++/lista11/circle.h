#ifndef CIRCLE_INCLUDED
#define CIRCLE_INCLUDED
#include "surf.h"

struct circle : public surf
{
	double x; // Position of center.
	double y;
	double radius;
	circle() = default;
	circle(double ix, double iy, double iradius)
		: x(ix), y(iy), radius(iradius) { }
	circle(const circle& c)
		: x(c.x), y(c.y), radius(c.radius) { }
	circle(circle&& c)
		: x(std::move(c.x)), y(std::move(c.y)), radius(std::move(c.radius)) { }
	double area( ) const override;
	double circumference( ) const override;
	circle* clone( ) const & override;
	circle* clone( ) && override;
	void print( std::ostream& ) const override;
};

#endif