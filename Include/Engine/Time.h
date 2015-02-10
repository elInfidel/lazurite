// ---------------------------------------------------------------------------
// Time.h
// A class for keeping track of time.
//
// Original author: <Liam Parker>
// Date created: 3/11/2014
// ---------------------------------------------------------------------------
#ifndef _TIME_H_
#define _TIME_H_

namespace lazurite
{
	class Time
	{
	public:
		Time();
		~Time();
		
		static void Update();
		
		// Getters
		static double GetDeltaTime();
		static double GetCurrentTime();
	
	private:
		static double currentTime;
		static double previousTime;
		static double deltaTime;
	};
}

#endif //_TIME_H_