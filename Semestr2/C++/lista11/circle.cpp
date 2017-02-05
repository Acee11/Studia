#include "circle.h"

double circle::area() const
{
	return M_PI * radius * radius;
}

double circle::circumference() const 
{
	return 2 * M_PI * radius;
}

circle* circle::clone() const &
{
	return new circle(*this);
}

circle* circle::clone() &&
{
	return new circle(*this);
}

void circle::print(std::ostream& out) const
{
	out << "circle " << x << " " << y << " " << radius << std::endl;
}