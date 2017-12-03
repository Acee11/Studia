#include "Console.hpp"

#include <iostream>

using namespace std;

void Console::addHandler(unique_ptr<CommandHandler> handler)
{
    handlers.push_back(move(handler));
}

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
    for (const auto& handler : handlers)
    {
        if (handler->handle(data.command, data.parameters) == CommandHandler::Result::Accepted)
            return true;
    }
    return false;
}
