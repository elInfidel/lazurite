#pragma once
#include <string>

using std::string;

class FileIO
{
public:

	// Performs a synchronous read of a filePath placing contents into the fileData buffer
	static bool Read(const char* filePath, string& fileData);
	// Performs a synchronous write with file data passed in
	static bool Write(const char* filePath, const string& fileData);

private:

	FileIO() = delete;
	~FileIO() = delete;
};
