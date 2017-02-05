#include <iostream>
#include "rectangle.h"
#include "triangle.h"
#include "circle.h"
#include "surface.h"
#include <vector>
#define RECT_TEST 0
#define TRIANGLE_TEST 0
#define CIRCLE_TEST 0
#define SURFACE_TEST 0

int main()
{
	circle p1(1,1,1);
	circle p2(1,1,1);
	surface s1(p1);
	surface s2(p2);
	s1 = s2;
	s1 = surface(p1);
	s2 = circle(2,2,2);
	std::cout << s1 << std::endl << s2;
#if RECT_TEST
	rectangle r(1.1234,2,3,4);
	rectangle* ptr = r.clone();
	
	std::cout << r.area() << "  "
		<< r.circumference() << " "
		<< std::endl; 
	ptr->print(std::cout);
	std::cout << ptr->area() << std::endl;
	r.print(std::cout);
#endif

#if TRIANGLE_TEST
	triangle t(4.321, 5, 6.7, 8.9, 10.11, 11.12);
	triangle* ptr1 = triangle(1,2,3,4,5,6).clone();

	std::cout << t.area() << "  "
		<< t.circumference() << " "
		<< std::endl; 
	ptr1->print(std::cout);
	std::cout << ptr1->area() << " " << ptr1->circumference() << std::endl;
	t.print(std::cout);
#endif

#if CIRCLE_TEST
	circle c(4.321, 5, 6.7);
	circle* ptr2 = circle(1,2,3).clone();

	std::cout << c.area() << "  "
		<< c.circumference() << " "
		<< std::endl; 
	ptr2->print(std::cout);
	std::cout << ptr2->area() << " " << ptr2->circumference() << std::endl;
	c.print(std::cout);
#endif

#if SURFACE_TEST
	rectangle r1(1,2,5,10);
	surface s(r1);

	std::vector<surface> vect = {rectangle(1,2,3,4), r1, circle(1,3,37), triangle(1,1,4,4,2,5)};

	std::cout << vect;

	print_statistics(vect);

#endif

	return 0;
}