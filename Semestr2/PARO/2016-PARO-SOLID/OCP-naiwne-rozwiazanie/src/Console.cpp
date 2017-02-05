#include "Console.hpp"
#include "Functions.hpp"

#include <iostream>

using namespace std;

void Console::run()
{
    string line;
    while (true)
    {
        getline(cin, line);
        const auto data = parser.parse(line);
        if (not handle(data))
            cout << "*** Unknown command! ***" << endl;
    }
}

bool Console::handle(const Parser::Data& data)
{
    if (data.command == "quit")
        Functions::quit();
    else if (data.command == "print")
        Functions::print(data.parameters[0]);
    else
        return false;
    return true;
}
