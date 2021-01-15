#include "util.h"

void log_error(std::string error, std::string name)
{
    // get current time stamp
    time_t now = std::time(0);
    const char* timestamp = ctime(&now);

    // log error
    std::ofstream error_log;
    error_log.open("logs/" + name, std::ios::app);
    error_log << timestamp  << ">> " << error << std::endl;
    error_log.close();
}
