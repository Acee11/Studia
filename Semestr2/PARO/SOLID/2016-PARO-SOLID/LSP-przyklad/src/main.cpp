#include <GeometricCalculator.hpp>
#include <Rectangle.hpp>
#include <Square.hpp>
#include <iostream>
#include <memory>


int main()
{
   Shapes shapes;
   shapes.push_back(std::make_shared<Rectangle>(1,2));
   shapes.push_back(std::make_shared<Rectangle>(3,4));
   shapes.push_back(std::make_shared<Square>(2));
   shapes.push_back(std::make_shared<Square>(3));

   GeometricCalculator geometricCalculator(shapes);
   std::cout<<"summed area is equal: " << geometricCalculator.calculateSumArea() << std::endl;

}
