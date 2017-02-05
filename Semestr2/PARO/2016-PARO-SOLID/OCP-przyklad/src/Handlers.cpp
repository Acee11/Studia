#include "Handlers.hpp"

#include <iostream>

using namespace std;

CommandHandler::Result Quitter::handle(const string& command, const vector<string>& parameters) const
{
    if (command != "quit")
        return Result::Declined;
    cout << "Console has quitted!" << endl;
    exit(0);
}

CommandHandler::Result Printer::handle(const string& command, const vector<string>& parameters) const
{
    if (command != "print")
        return Result::Declined;
    cout << parameters[0] << endl;
    return Result::Accepted;
}
