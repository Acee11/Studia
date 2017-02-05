#pragma once
#include <vector>
#include <memory>
#include <Rectangle.hpp>

typedef std::vector<std::shared_ptr<Rectangle>> Rectangles;

class GeometricCalculator
{
public:
    GeometricCalculator(Rectangles rect)
        :rectangles(rect)
    {
        initRectangles();
    }

    double calculateSumArea()
    {
        double sum = 0;

        for(auto rect: rectangles)
        {
            sum += rect->calculateArea();
        }
        return sum;
    }
private:
    void initRectangles()
    {
        for(auto rect: rectangles)
        {
            rect->setWidth(5);
            rect->setHeight(10);
        }
    }
private:
    Rectangles rectangles;
};

