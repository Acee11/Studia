#pragma once
#include <Shape.hpp>

class Rectangle: public Shape
{
public:
    virtual void setHeight(double x){height =x;}
    virtual void setWidth(double x){width =x;}
    double calculateArea() const override {return width*height;}

protected:
    double width;
    double height;
};
