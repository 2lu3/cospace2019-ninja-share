#include "LogErrorTools.h"

#define FILE_NAME_LENGTH 20

char error_file_name[FILE_NAME_LENGTH] = "error_file.txt";
char log_file_name[FILE_NAME_LENGTH] = "log_file.txt";
FILE *error_file = NULL;
FILE *log_file = NULL;
FILE *output_file = NULL;

// World1の最初に実行する
int logErrorToolsSetup(void)
{
	error_file = fopen(error_file_name, "w");
	if (error_file == NULL)
	{
		printf("LogErrorTools.c setup() : failed to create error file\n");
	}
	log_file = fopen(log_file_name, "w");
	if (log_file == NULL)
	{
		printf("LogErrorTools.c setup() : failed to create log file");
	}
	return 1;
}

void delErrorFile()
{
	char command[FILE_NAME_LENGTH + 10];
	sprintf(command, "del %s\n", error_file_name);
	system(command);
}

void delLogFile()
{
	char command[FILE_NAME_LENGTH + 10];
	sprintf(command, "del %s\n", log_file_name);
	system(command);
}

void delOutFile(char file_name[])
{
	char command[FILE_NAME_LENGTH + 10];
	sprintf(command, "del %s\n", file_name);
	system(command);
}

void convertMessageFormat(char *message)
{
	sprintf(message, "%d %s", getRepeatedNum(), message);
}

bool writeErrorMessage(char *message)
{
	convertMessageFormat(message);
	fprintf(error_file, "%s\n", message);
	return true;
}

// mode = default mode
bool errorMessage(char *message)
{
	if (getDefaultRunMode() <= getRunMode())
	{
		logMessage(message);
		bool result = writeErrorMessage(message);
		return result;
	}
	return true;
}

// mode = option
bool errorMessageOption(char *message, enum Mode option)
{
	if (option <= getRunMode())
	{
		logMessageOption(message, option);
		bool result = writeErrorMessage(message);
		return result;
	}
	return true;
}

bool writeLogMessage(char *message)
{
	convertMessageFormat(message);
	fprintf(log_file, "%s\n", message);
	return true;
}

// mode = default mode
bool logMessage(char *message)
{
	if (getDefaultRunMode() <= getRunMode())
	{
		bool result = writeLogMessage(message);
		if (MODE_DEBUG <= getRunMode())
		{
			convertMessageFormat(message);
			printf("%s\n", message);
		}
		return result;
	}
	return true;
}

bool logMessageOption(char *message, enum Mode option)
{
	if (option <= getRunMode())
	{
		bool result = writeLogMessage(message);
		if (MODE_DEBUG <= getRunMode())
		{
			convertMessageFormat(message);
			printf("%s\n", message);
		}
		return result;
	}
	return true;
}

bool outputData(char file_name[], char *message)
{
	if (getDefaultRunMode() < getRunMode())
	{
		return true;
	}
	output_file = fopen(file_name, "a");
	if (output_file == NULL)
	{
		char error_message[100] = "outputData() : Failed to output data file";
		printf("%s\n", error_message);
		errorMessage(error_message);
		return false;
	}
	if (getDefaultRunMode() >= MODE_DEBUG)
	{
		printf("%s\n", message);
	}
	fprintf(output_file, "%s\n", message);
	fclose(output_file);
	return true;
}

bool outputDataOption(char file_name[], char *message, enum Mode option)
{
	if (option < getRunMode())
	{
		return true;
	}
	bool result = outputData(file_name, message);
	if (getDefaultRunMode() < MODE_DEBUG && option >= MODE_DEBUG)
	{
		printf("%s\n", message);
	}
	return result;
}
