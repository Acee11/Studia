#pragma once
#include <memory>
#include <string>
#include <vector>

#include <WidgetsFactory.hpp>
#include <Widgets.hpp>

class Display
{
public:
    Display(const std::shared_ptr<WidgetsFactory>& widgetsFactory);
    void display();

private:
    std::vector< std::shared_ptr<Widget> > allWidgets;
};

