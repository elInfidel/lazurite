#pragma once
#include <string>
class Resource
{
public:
	Resource();
	virtual ~Resource();

	unsigned int GetGUID();

	virtual void Load() = 0;
	virtual void Unload() = 0;
private:
	std::string path;
};

