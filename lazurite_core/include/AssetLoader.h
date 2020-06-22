#pragma once
#include <string>

template <class T>
class AssetLoader {
	virtual T Load(std::string path) = 0;
};