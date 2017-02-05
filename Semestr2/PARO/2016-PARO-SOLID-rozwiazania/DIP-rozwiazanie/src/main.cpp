#include <Logger.hpp>
#include <SqlDataSaver.hpp>
#include <Saver.hpp>

int main()
{
    SqlAdress adress("127.0.0.1");
    std::unique_ptr<SqlDataSaver> sqlDataSaver(new SqlDataSaver(adress));
    Logger logger(std::move(sqlDataSaver));
    logger.log("ciekawy log 1");
    logger.log("ciekawy log 2");
    logger.log("ciekawy log 3");
 }
