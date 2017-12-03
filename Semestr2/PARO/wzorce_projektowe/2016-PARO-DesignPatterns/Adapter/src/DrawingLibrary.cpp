#include <DrawingLibrary.hpp>
#include <iostream>

namespace DrawingLibrary
{

void Rectangle::draw(int x1, int y1, int x2, int y2)
{
    std::cout<< "I have just drawn a rectangle with corners at points: "
             << "(" << x1 << ","<<y1<<") ; "
             << "(" << x2 << ","<<y2<<") \n";
}

}

