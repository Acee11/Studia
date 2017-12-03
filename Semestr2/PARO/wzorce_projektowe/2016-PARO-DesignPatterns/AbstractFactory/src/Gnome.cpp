#include <Gnome.hpp>
#include <iostream>


void GnomeLabel::draw() const
{
    std::cout << "GnomeLabel\n";
}


void GnomeSlider::draw() const
{
    std::cout << "GnomeSlider\n";
}


void GnomeSlider::onSlide() const
{
    std::cout << "I can slide on Gnome\n";
}


void GnomeButton::draw() const
{
    std::cout << "GnomeLabel\n";
}


void GnomeButton::onClick() const
{
    std::cout << "I can click on Gnome\n";
}
