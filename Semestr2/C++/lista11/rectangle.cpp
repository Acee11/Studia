#include "rectangle.h"

double rectangle::area() const 
{
	return (x2 - x1) * (y2 - y1);
}

double rectangle::circumference() const
{
	return 2*(x2-x1) + 2*(y2-y1);
}

rectangle* rectangle::clone() const &
{
	return new rectangle(*this);
}

rectangle* rectangle::clone( ) &&
{
	std::cout << "aaa\n";
	rectangle* ptr = new rectangle(*this);
	return ptr;
}

void rectangle::print(std::ostream& out) const
{
	out << "rectangle " << x1 << " " << y1 << " " << x2 << " " << y2 << std::endl;
}

