#include <Kde.hpp>
#include <iostream>


void KdeLabel::draw() const
{
    std::cout << "KdeLabel\n";
}


void KdeSlider::draw() const
{
    std::cout << "KdeSlider\n";
}


void KdeSlider::onSlide() const
{
    std::cout << "I can slide on Kde\n";
}


void KdeButton::draw() const
{
    std::cout << "KdeDivider\n";
}


void KdeButton::onClick() const
{
    std::cout << "I can click on Kde\n";
}
