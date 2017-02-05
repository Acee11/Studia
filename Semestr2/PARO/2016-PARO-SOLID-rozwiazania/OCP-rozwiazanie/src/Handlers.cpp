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
    for (auto param: parameters)
        cout << param << " ";
    cout << endl;
    return Result::Accepted;
}

CommandHandler::Result Sumator::handle(const string& command, const vector<string>& parameters) const
{
    if (command != "sum")
        return Result::Declined;
    int sum = 0;
    for (auto param: parameters)
        sum += std::stoi(param);
    cout << "sum is equal " << sum << std::endl;
    return Result::Accepted;
}
