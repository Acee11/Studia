#pragma once

#include <vector>
#include <string>

class CommandHandler
{
public:
    enum class Result
    {
        Declined,
        Accepted
    };
    virtual Result handle(const std::string& command, const std::vector<std::string>& parameters) const = 0;
};
