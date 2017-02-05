#pragma once
#include <vector>
#include <memory>
#include <Rectangle.hpp>

typedef std::vector<std::shared_ptr<Shape>> Shapes;

class GeometricCalculator
{
public:
    GeometricCalculator(Shapes shp)
        :shapes(shp)
    {
    }

    double calculateSumArea()
    {
        double sum = 0;

        for(auto shape: shapes)
        {
            sum += shape->calculateArea();
        }
        return sum;
    }  
private:
    Shapes shapes;
};

