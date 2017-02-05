#ifndef TRIANGLE_INCLUDED
#define TRIANGLE_INCLUDED
#include "surf.h"

struct triangle : public surf
{
	double x1, y1; // Positions of corners.
	double x2, y2;
	double x3, y3;
	triangle() = default;
	triangle(double ix1, double iy1, double ix2,
			 double iy2, double ix3, double iy3)
		: x1(ix1), y1(iy1), x2(ix2),
		  y2(iy2), x3(ix3), y3(iy3) { }
	triangle(const triangle& t)
		: x1(t.x1), y1(t.y1), x2(t.x2),
		  y2(t.y2), x3(t.x3), y3(t.y3) { }
	triangle(triangle&& t)
		: x1(std::move(t.x1)), y1(std::move(t.y1)),
		  x2(std::move(t.x2)), y2(std::move(t.y2)),
		  x3(std::move(t.x3)), y3(std::move(t.y3)) { }
	double area( ) const override;
	double circumference( ) const override;
	triangle* clone( ) const & override;
	triangle* clone( ) && override;
	void print( std::ostream& ) const override;
};

#endif