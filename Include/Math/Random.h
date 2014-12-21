// ---------------------------------------------------------------------------
// Random.h
// An object that can be used to generate random numbers based on a seed
//
// Original author: <Liam Parker>
// Date Created: 14/12/2014
// ---------------------------------------------------------------------------
#ifndef _RANDOM_H_
#define _RANDOM_H_

class Random
{
public:
	// Constructs an instance of Random
	Random();
	~Random();
	// Constructs an instance of Random with the seed argument
	Random(unsigned int seed);

private:
	unsigned int seed;
};

#endif //_RANDOM_H_