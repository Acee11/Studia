#ifndef RECTANGLE_INCLUDED
#define RECTANGLE_INCLUDED
#include "surf.h"

struct rectangle : public surf
{
	double x1, y1;
	double x2, y2;
	rectangle() = default;
	rectangle(double ix1, double iy1, double ix2, double iy2)
		: x1(ix1), y1(iy1), x2(ix2), y2(iy2) { }	
	rectangle(const rectangle& r)
		: x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) { }
	rectangle(rectangle&& r)
		: x1(std::move(r.x1)), y1(std::move(r.y1)),
		  x2(std::move(r.x2)), y2(std::move(r.y2)) { }
	double area( ) const override;
	double circumference( ) const override;
	rectangle* clone( ) const & override;
	rectangle* clone( ) && override;
	void print( std::ostream& ) const override;
};

#endif