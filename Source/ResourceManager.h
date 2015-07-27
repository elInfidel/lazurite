#pragma once
#include "Resource.h"
#include <unordered_map>
#include <string>

using namespace std;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

private:
	unordered_map<string, Resource*> resources;
};

