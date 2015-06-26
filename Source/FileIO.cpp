#include "FileIO.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>

using std::ifstream;
using std::ofstream;

FileIO::FileIO()
{

}

FileIO::~FileIO()
{

}

bool FileIO::SyncRead(const char* filePath, string* fileData)
{
	// Open a the file path requested
	ifstream file(filePath);

	// Read file data if opened successfully
	if (file)
	{
		while (file)
		{
			string buffer;
			getline(file, buffer);
			fileData->append(buffer + "\n");
		}
		file.close();
	}
	else
		return false;

	return true;
}

void FileIO::AsyncRead(const char* filePath, string* fileData)
{
	// TODO: 
}

bool FileIO::SyncWrite(const char* filePath, const string* fileData)
{
	ofstream file(filePath);

	if(file)
	{
		file.write(fileData->c_str(), fileData->length());
	}
	else 
		return false;

	std::cout << "INFO - Successfully wrote " << fileData->length() << " bytes of data to " << filePath << "\n";
	file.close();

	return true;
}

bool FileIO::AsyncWrite(const char* filePath, const string* fileData)
{
	return false; // TODO: 
}
