#pragma once

namespace PicturesLibrary
{

class Rectangle
{
public:
    virtual void draw(int x1, int y1, int width, int height) = 0;
};

class Square
{
public:
    virtual void draw(int x1, int y1, int length) = 0;
};

class Picture
{
public:
    void drawPicture(Rectangle& rectangle, Square& sqare);
};

}
