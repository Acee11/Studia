#include <memory>
#include <Logger.hpp>
#include <SqlDataSaver.hpp>

int main()
{
    SqlAdress adress("127.0.0.1");
    //auto dataSaver = std::make_unique<SqlDataSaver>(SqlAdress);
	std::unique_ptr<SqlDataSaver> dataSaver(new SqlDataSaver(adress));
    Logger logger(std::move(dataSaver));
    logger.log("ciekawy log 1");
    logger.log("ciekawy log 2");
    logger.log("ciekawy log 3");
 }
