#pragma once
#include <sstream>

class Logger
{
public:
	static Logger* GetInstance();

private:
	Logger();
	~Logger();

	static Logger* singleton;
    
    std::stringstream output;

    std::string getBufferContents();
};

