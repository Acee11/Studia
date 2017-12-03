#pragma once
#include <Database.hpp>



class Chart
{
public:
    Chart(Database& db);
    ~Chart();
    void plot();
private:
	unsigned id;
    Database& database;
};

class Calculator
{
public:
    Calculator(Database& db);
    ~Calculator();
    void recalculate();
private:
	unsigned id;
    Database& database;
};

class EmailSender
{
public:
    EmailSender(Database& db);
    ~EmailSender();
    void send();
private:
	unsigned id;
    Database& database;
};
