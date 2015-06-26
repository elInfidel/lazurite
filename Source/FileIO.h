#pragma once
#include <string>

using std::string;

class FileIO
{
public:
	// Performs a synchronous read of a filePath placing contents into the fileData buffer
	static bool SyncRead(const char* filePath, string* fileData);
	// Performs an asynchronous read dumping file contents into file data buffer
	// Note - Invokes callback function when reading is complete
	static void AsyncRead(const char* filePath, string* fileData);
	// Performs a synchronous write with file data passed in
	static bool SyncWrite(const char* filePath, const string* fileData);
	// Performs an asynchronous write with file data passed in
	// Note - Invokes callback function when writing is complete
	static bool AsyncWrite(const char* filePath, const string* fileData);

private:
	FileIO();
	~FileIO();
};

