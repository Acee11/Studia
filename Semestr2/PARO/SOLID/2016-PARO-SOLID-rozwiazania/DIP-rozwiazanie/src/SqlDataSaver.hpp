#pragma once
#include <string>
#include <Saver.hpp>

class SqlAdress
{
public:
    SqlAdress(std::string adress)
        :sqlAdress(adress)  {}

    std::string get()  {return sqlAdress;}
private:
    std::string sqlAdress;
};


class SqlDataSaver: public Saver
{
public:
    SqlDataSaver(SqlAdress adress);
    void saveData(std::string data);
};

