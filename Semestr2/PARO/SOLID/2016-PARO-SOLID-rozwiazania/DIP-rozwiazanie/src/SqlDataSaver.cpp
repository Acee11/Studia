#include <SqlDataSaver.hpp>
#include <iostream>


SqlDataSaver::SqlDataSaver(SqlAdress adress)
{
    std::cout << "SQL data Saver created. Connection established at: " << adress.get() << std::endl;
}

void SqlDataSaver::saveData(std::string data)
{
    std::cout << "saving data to sql db: " << data << std::endl;
}
