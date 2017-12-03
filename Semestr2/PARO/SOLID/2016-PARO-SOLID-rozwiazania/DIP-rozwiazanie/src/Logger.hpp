#pragma once
#include <string>
#include <memory>
#include <Saver.hpp>

class Logger
{
public:
    Logger(std::unique_ptr<Saver> saver);
    void log(std::string log);
private:
    std::unique_ptr<Saver> dataSaver;
};

