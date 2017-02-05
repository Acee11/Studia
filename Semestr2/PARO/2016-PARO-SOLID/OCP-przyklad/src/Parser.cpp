#include "Parser.hpp"

#include <iterator>

using namespace std;

Parser::Data Parser::parse(const string& line)
{
    if (line.empty())
            return {};
    ss.clear();
    ss << line;
    return readData();
}

Parser::Data Parser::readData()
{
    Data result;
    ss >> result.command;
    result.parameters = readParameters();
    return result;
}

vector<string> Parser::readParameters()
{
    return vector<string>(istream_iterator<string>(ss), istream_iterator<string>());
}