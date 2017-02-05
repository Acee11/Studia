#pragma once
#include <Rectangle.hpp>

class Square: public Shape
{
public:
    void setSide(double x){side = x;}
    double calculateArea() const override{return side*side;}
private:
    double side;
};
