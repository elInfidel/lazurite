#include "subsystem/logger.h"

#include <iostream>

// Static data
Logger* Logger::singleton;

Logger::Logger()
{
	std::streambuf * old = std::cout.rdbuf(output.rdbuf());
}

Logger::~Logger()
{
	delete singleton;
}

Logger* Logger::GetInstance()
{
	if (singleton == nullptr)
		singleton = new Logger();
	return singleton;
}

std::string Logger::getBufferContents() 
{
    return output.str();
}