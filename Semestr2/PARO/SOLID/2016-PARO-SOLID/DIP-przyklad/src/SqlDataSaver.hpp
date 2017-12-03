#pragma once
#include <string>
#include <Saving.hpp>


class SqlAdress
{
public:
    SqlAdress(std::string adress)
        :sqlAdress(adress)  {}

    std::string get()  {return sqlAdress;}
private:
    std::string sqlAdress;
};


class SqlDataSaver : public Saving
{
public:
    SqlDataSaver(SqlAdress adress);
    virtual void saveData(std::string data);
};

