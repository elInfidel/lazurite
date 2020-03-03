#pragma once

/*
	Represents a platform capable of tracking system metrics.
	Not used now, will abstract away platform specific logic.
	TODO: Draw this out into platform specific files.
*/
class MetricsGatheringPlatform 
{
public:
	virtual void getCPUMetrics() = 0;
	virtual void getMemoryMetrics() = 0;
	virtual void getGPUMetrics() = 0;
};

struct CPUMetrics 
{
	unsigned int concurrentThreadsAvailable = 0;
	double cpuTotalUsage = 0;
	double cpuProcessUsage = 0;
};

struct MemoryMetrics
{
	unsigned long long physicalUsed = 0;
	unsigned long long physicalTotal = 0;
	unsigned long long virtualUsed = 0;
	unsigned long long virtualTotal = 0;
};

struct GPUMetrics
{
	// TODO
	// videoMemoryUsage
	// videoMemoryTotal
	// Model
};

/*
	The metrics subsystem gives access to various
*/
class Metrics
{
public:
	static Metrics* GetInstance();
	void Update();

	CPUMetrics lastCpu;
	MemoryMetrics lastMemory;

private:
	Metrics();
	~Metrics();

	static Metrics* singleton;
};