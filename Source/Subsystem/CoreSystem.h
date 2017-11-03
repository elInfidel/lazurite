#pragma once

class CoreSystem
{
public:
	bool IsInitialized();

	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;

protected:
	CoreSystem();
	virtual ~CoreSystem();

	static bool isInitialized;
};

