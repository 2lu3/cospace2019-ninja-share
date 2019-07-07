#include "LogErrorTools.hpp"
#include "CommonTools.hpp"

using namespace std;
LogErrorMessage logErrorMessage;
string error_file_name("error_file.txt");
string log_file_name("log_file.txt");

void LogErrorMessage::delErrorFile()
{
	if (remove(("./" + error_file_name).c_str()))
	{
		cerr << "failed to delete Error file" << endl;
	}
}

void LogErrorMessage::delLogFile()
{
	if (remove(("./" + log_file_name).c_str()))
	{
		errorMessage("failed to delete Log file", MODE_MATCH);
	}
}

void LogErrorMessage::delOutFile(string file_name)
{
	if (remove(("./" + file_name).c_str()))
	{
		errorMessage("failed to delete " + file_name + " file", MODE_MATCH);
	}
}

string LogErrorMessage::createMessage(string message)
{
	message = to_string(getRepeatedNum()) + " " + message;
	return message;
}

bool LogErrorMessage::writeErrorMessage(string message)
{
	ofstream error_file("./" + error_file_name, ios::app);
	if (!error_file)
	{
		cerr << "writeErrorMessage() : Failed to open error file"
			 << "\n";
		return false;
	}
	error_file << createMessage(message) << "\n";
	return true;
}

// mode = default mode
bool LogErrorMessage::errorMessage(string message)
{
	return errorMessage(message, getDefaultRunMode());
}

// mode = option
bool LogErrorMessage::errorMessage(string message, Mode option)
{
	if (option <= getRunMode())
	{
		logMessage(message, option);
		if (getIsOutputErrorMessage2Console())
		{
			cout << createMessage(message) << "\n";
		}
		return writeErrorMessage(message);
	}
	return true;
}

bool LogErrorMessage::writeLogMessage(string message)
{
	ofstream log_file("./" + log_file_name, ios::app);
	if (!log_file)
	{
		cerr << "LogMessage() : Failed to open log file"
			 << "\n";
		return false;
	}
	log_file << createMessage(message) << "\n";
	return true;
}

// mode = default mode
bool LogErrorMessage::logMessage(string message)
{
	return logMessage(message, getDefaultRunMode());
}

bool LogErrorMessage::logMessage(string message, Mode option)
{
	if (option <= getRunMode())
	{
		bool result = writeLogMessage(message);
		if (getIsOutputLogMessage2Console())
		{
			cout << createMessage(message) << "\n";
		}
		return result;
	}
	return true;
}

bool LogErrorMessage::writeOutputData(string file_name, string message)
{
	ofstream output_file("./" + file_name, ios::app);
	if (!output_file)
	{
		cerr << "writeOutputData() : Failed to open output file"
			 << "\n";
		return false;
	}
	output_file << message;
	return true;
}

bool LogErrorMessage::outputData(string file_name, string message)
{
	return outputData(file_name, message, getDefaultRunMode());
}

bool LogErrorMessage::outputData(string file_name, string message, Mode option)
{
	if (option <= getRunMode())
	{
		return writeOutputData(file_name, message);
	}
	return true;
}
