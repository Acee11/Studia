#pragma once
#include <Widgets.hpp>

class GnomeLabel :  public Label
{
public:
    void draw() const override;
};

class GnomeSlider : public Slider
{
public:
    void draw() const override;

    void onSlide() const override;
};

class GnomeButton : public Button
{
public:
    void draw() const override;

    void onClick() const override;
};

