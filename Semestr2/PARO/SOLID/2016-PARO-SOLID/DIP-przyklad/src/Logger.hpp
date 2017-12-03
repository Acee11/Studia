#pragma once
#include <string>
#include <memory>
#include <Saving.hpp>


class Logger
{
public:
    Logger(std::unique_ptr<Saving> saving);
    void log(std::string log);
private:
    std::unique_ptr<Saving> dataSaver;
};



