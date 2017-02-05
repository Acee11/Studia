#include "Functions.hpp"

#include <iostream>

using namespace std;

void Functions::print(std::string str)
{
    cout << str << endl;
}

void Functions::quit()
{
    cout << "Console has quitted!" << endl;
    exit(0);
}