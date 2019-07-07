#ifndef LOG_ERROR_TOOLS
#define LOG_ERROR_TOOLS

#include "CospaceSettings.hpp"

class LogErrorMessage
{
public:
    bool errorMessage(std::string message);
    bool logMessage(std::string message);
    bool errorMessage(std::string message, Mode option);
    bool logMessage(std::string message, Mode option);
    bool outputData(std::string file_name, std::string message);
    bool outputData(std::string file_name, std::string message, Mode option);
    void delErrorFile();
    void delLogFile();
    void delOutFile(std::string file_name);

private:
    std::string createMessage(std::string message);
    bool writeLogMessage(std::string message);
    bool writeErrorMessage(std::string message);
    bool writeOutputData(std::string file_name, std::string message);
};

extern LogErrorMessage logErrorMessage;

#endif // !LOG_ERROR_TOOLS
