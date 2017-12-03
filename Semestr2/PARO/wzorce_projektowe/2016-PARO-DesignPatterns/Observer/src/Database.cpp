#include <Database.hpp>
#include <Clients.hpp>
#include <iostream>

Database::Database()
    : data("dummy data")
{
}

// void Database::initialize(Chart* chart, Calculator* calculator, EmailSender* emailSender)
// {
//     chartHandler = chart;
//     calculatorHandler = calculator;
//     emailSenderHandler = emailSender;
// }

void Database::changeData(std::string newData)
{
    data = newData;
    onChange();
}

void Database::onChange()
{
    observer.notify();
}

std::string Database::getData(std::string query)
{
    return "data for " + query + " is: " + data;
}
