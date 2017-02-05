#include <GeometricCalculator.hpp>
#include <Rectangle.hpp>
#include <Square.hpp>
#include <iostream>
#include <memory>


int main()
{
   Rectangles rectangles;
   rectangles.push_back(std::make_shared<Rectangle>());
   rectangles.push_back(std::make_shared<Rectangle>());
   rectangles.push_back(std::make_shared<Square>());
   rectangles.push_back(std::make_shared<Square>());

   GeometricCalculator geometricCalculator(rectangles);
   std::cout<<"summed area is equal: " << geometricCalculator.calculateSumArea() << std::endl;

}
