#pragma once
#include <string>

struct Saver
{
    virtual void saveData(std::string data) = 0;
};
