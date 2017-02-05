#pragma once
#include <Point.hpp>
#include <Rectangle.hpp>


class Square: public Rectangle
{
public:
    void setHeight(double x){height =x; width =x;}
    void setWidth(double x){height =x; width =x;}
};
