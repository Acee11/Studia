#include <Logger.hpp>

Logger::Logger(std::unique_ptr<Saver> saver)
    :dataSaver(std::move(saver))
{
}

void Logger::log(std::string log)
{
    dataSaver->saveData(log);
}


