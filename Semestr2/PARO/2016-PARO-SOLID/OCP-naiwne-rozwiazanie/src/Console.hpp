#pragma once

#include "Parser.hpp"

class Console
{
public:
    void run();

private:
    bool handle(const Parser::Data& data);

    Parser parser;
};
