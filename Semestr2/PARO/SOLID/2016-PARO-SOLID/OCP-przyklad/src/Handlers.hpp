#pragma once

#include "CommandHandler.hpp"

using namespace std;

struct Quitter : CommandHandler
{
    Result handle(const string&, const vector<string>&) const override;
};

struct Printer : CommandHandler
{
    Result handle(const string&, const vector<string>&) const override;
};

struct Sumator : CommandHandler
{
	Result handle(const string&, const vector<string>&) const override;
};