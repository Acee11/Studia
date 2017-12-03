#pragma once
#include <Point.hpp>
#include <Shape.hpp>


class Square : public Shape
{
private:
	double side;
public:
	Square(double side)
		:side(side)
	{}
    void setSide(double x){side = x;}
    double calculateArea() const override {return side*side;}
};
