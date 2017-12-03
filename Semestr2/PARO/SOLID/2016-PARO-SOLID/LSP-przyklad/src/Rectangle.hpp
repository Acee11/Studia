#pragma once
#include <Point.hpp>
#include <Shape.hpp>

class Rectangle : public Shape
{
public:
	Rectangle(double width, double height)
		: width(width), height(height)
	{}

    virtual void setHeight(double x){height = x;}
    virtual void setWidth(double x){width = x;}
    double calculateArea() const override {return width*height;} 

protected:
    double width;
    double height;
};
