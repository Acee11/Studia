#pragma once
#include <Widgets.hpp>

class KdeLabel : public Label
{
public:
    void draw() const override;
};



class KdeSlider : public Slider
{
public:
    void draw() const override;
    void onSlide() const override;
};



class KdeButton : public Button
{
public:
    void draw() const override;
    void onClick() const override;
};

