#include "triangle.h"

double triangle::area() const
{
	double p = 0.5 * circumference();
	double a = distance(x1,y1,x2,y2);
	double b = distance(x2,y2,x3,y3);
	double c = distance(x1,y1,x3,y3);
	return p * (p - a) * (p - b) * (p - c);
}

double triangle::circumference() const
{
	return distance(x1,y1,x2,y2) + distance(x2,y2,x3,y3) + distance(x1,y1,x3,y3);
}

triangle* triangle::clone() const &
{
	return new triangle(*this);
}

triangle* triangle::clone() &&
{
	return new triangle(*this);
}

void triangle::print(std::ostream& out) const
{
	out << "triangle " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << std::endl;
}
