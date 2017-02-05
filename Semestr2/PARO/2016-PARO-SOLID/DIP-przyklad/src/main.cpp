#include <Logger.hpp>
#include <SqlDataSaver.hpp>

int main()
{
    SqlAdress adress("127.0.0.1");
    Logger logger(adress);
    logger.log("ciekawy log 1");
    logger.log("ciekawy log 2");
    logger.log("ciekawy log 3");
 }
