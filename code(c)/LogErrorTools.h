#ifndef LOG_ERROR_TOOLS
#define LOG_ERROR_TOOLS

#include <stdio.h>
#include <stdbool.h>
#include "CommonTools.h"

int logErrorToolsSetup(void);
bool errorMessage(char *message);
bool logMessage(char *message);
bool errorMessageOption(char *message, enum Mode option);
bool logMessageOption(char *message, enum Mode option);
bool outputData(char file_name[], char *message);
bool outputDataOption(char file_name[], char *message, enum Mode option);
void delErrorFile();
void delLogFile();
void delOutFile(char file_name[]);

#endif // !LOG_ERROR_TOOLS
