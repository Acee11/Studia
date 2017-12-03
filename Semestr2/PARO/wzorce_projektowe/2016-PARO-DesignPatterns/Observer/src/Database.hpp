#pragma once

#include <string>
#include <Observer.hpp>




class Database
{
public:
    Database();
    //void initialize(Chart* chart, Calculator* calculator, EmailSender* emailSender); //try to remove second constructor!
    void changeData(std::string newData);
    std::string getData(std::string query);
    Observer observer;


private:
    void onChange();

    std::string data;

    // Chart* chartHandler;              //
    // Calculator* calculatorHandler;    //   try to remove these unlogic dependencies
    // EmailSender* emailSenderHandler;  //
};
