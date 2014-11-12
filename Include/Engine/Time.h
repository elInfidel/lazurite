// ---------------------------------------------------------------------------
// Time.h
// A class for keeping track of time.
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#ifndef _TIME_H_
#define _TIME_H_

class Time
{
public:
	Time();
	~Time();

	void Update();

	static double GetDeltaTime();
	static double GetCurrentTime();

private:
	static double currentTime;
	static double previousTime;
	static double deltaTime;
};

#endif //_TIME_H_