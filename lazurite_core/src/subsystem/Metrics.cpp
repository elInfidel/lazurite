#include "subsystem/metrics.h"
#include "windows.h"
#include "TCHAR.h"
#include "pdh.h"
#include <thread>

// Static data
Metrics* Metrics::singleton;

Metrics::Metrics()
{
	
}

Metrics::~Metrics()
{
	delete singleton;
}

Metrics* Metrics::GetInstance()
{
	if (singleton == nullptr)
		singleton = new Metrics();
	return singleton;
}

void Metrics::Update()
{
	
}