#pragma once

#include <vector>
#include <string>
#include <sstream>

class Parser
{
public:
    struct Data
    {
        std::string command;
        std::vector<std::string> parameters;
    };

    Data parse(const std::string& line);

private:
    Data readData();
    std::vector<std::string> readParameters();

    std::stringstream ss;
};
