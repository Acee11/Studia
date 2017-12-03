#pragma once
#include <Widgets.hpp>

class WindowsLabel : public Label
{
public:
    void draw() const override;
};


class WindowsSlider : public Slider
{
public:
    void draw() const override;
    void onSlide() const override;
};



class WindowsButton : public Button
{
public:
    void draw() const override;
    void onClick() const override;
};

