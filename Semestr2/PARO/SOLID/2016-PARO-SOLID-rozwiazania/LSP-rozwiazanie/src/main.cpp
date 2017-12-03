#include <GeometricCalculator.hpp>
#include <Rectangle.hpp>
#include <Square.hpp>
#include <Shape.hpp>
#include <iostream>
#include <memory>


std::shared_ptr<Shape> createRectangle()
{
    std::shared_ptr<Rectangle> rectangle(new Rectangle);
    rectangle->setHeight(10);
    rectangle->setWidth(5);
    return rectangle;
}

std::shared_ptr<Shape> createSquare()
{
    std::shared_ptr<Square> square(new Square);
    square->setSide(10);
    return square;
}

int main()
{
    Shapes shapes;
    shapes.push_back(createRectangle());
    shapes.push_back(createRectangle());
    shapes.push_back(createSquare());
    shapes.push_back(createSquare());

    GeometricCalculator geometricCalculator(shapes);
    std::cout<<"summed area is equal: " << geometricCalculator.calculateSumArea() << std::endl;

}
