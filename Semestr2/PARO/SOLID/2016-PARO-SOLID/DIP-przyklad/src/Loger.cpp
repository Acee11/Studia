#include <Logger.hpp>



Logger::Logger(std::unique_ptr<Saving> saving)
{
    dataSaver = std::move(saving);
}

void Logger::log(std::string log)
{
    dataSaver->saveData(log);
}


