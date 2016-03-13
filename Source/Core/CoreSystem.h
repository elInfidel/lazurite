#pragma once

class CoreSystem
{
public:
	bool IsInitialized();

protected:
	CoreSystem();
	virtual ~CoreSystem();

	static bool isInitialized;
};

