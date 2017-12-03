#include <PicturesLibrary.hpp>

namespace PicturesLibrary
{

void Picture::drawPicture(PicturesLibrary::Rectangle& rectangle,
                          PicturesLibrary::Square& sqare)
{
    rectangle.draw(0,0,15,10);
    sqare.draw(10,10,10);
}

}
