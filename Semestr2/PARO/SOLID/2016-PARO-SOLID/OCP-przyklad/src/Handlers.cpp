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

CommandHandler::Result Sumator::handle(const string& command, const vector<string>& parameters) const
{
	if (command != "sum")
    	return Result::Declined;
	int n1 = stoi(parameters[0]);
	int n2 = stoi(parameters[1]);
    cout << n1+n2 << endl;
    return Result::Accepted;
}
