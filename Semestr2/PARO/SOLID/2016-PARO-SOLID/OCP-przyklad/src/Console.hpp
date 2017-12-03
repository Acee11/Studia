#pragma once

#include <vector>
#include <memory>

#include "Parser.hpp"
#include "CommandHandler.hpp"

class Console
{
public:
    void addHandler(std::unique_ptr<CommandHandler> handler);
    void run();

private:
    bool handle(const Parser::Data& data);

    Parser parser;
    std::vector< std::unique_ptr<CommandHandler> > handlers;
};
