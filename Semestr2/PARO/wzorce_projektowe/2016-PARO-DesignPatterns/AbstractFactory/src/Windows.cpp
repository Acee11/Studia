#include <Windows.hpp>
#include <iostream>


void WindowsLabel::draw() const
{
    std::cout << "WindowsLabel\n";
}


void WindowsSlider::draw() const
{
    std::cout << "WindowsSlider\n";
}


void WindowsSlider::onSlide() const
{
    std::cout << "I can slide on Windows\n";
}


void WindowsButton::draw() const
{
    std::cout << "WindowsDivider\n";
}


void WindowsButton::onClick() const
{
    std::cout << "I can click on Windows\n";
}
