#pragma once
#include <string>

class SqlAdress
{
public:
    SqlAdress(std::string adress)
        :sqlAdress(adress)  {}

    std::string get()  {return sqlAdress;}
private:
    std::string sqlAdress;
};


class SqlDataSaver
{
public:
    SqlDataSaver(SqlAdress adress);
    void saveData(std::string data);
};

