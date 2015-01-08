// ---------------------------------------------------------------------------
// Mathf.h
// An interface to common mathematical functionality,
// not feature complete by any stretch of the word.
//
// Original author: <Liam Parker>
// Date Created: 10/12/2014
// ---------------------------------------------------------------------------
#ifndef _MATHF_H_
#define _MATHF_H_

#define PI 3.14159265359

#define DegToRad(degrees) (degrees * PI / 180.0)
#define RadToDeg(radians) (radians * 180.0 / PI)

class Mathf
{
public:
	Mathf();
	~Mathf();

	//Interpolates between to values by t
	static float Lerp(float from, float to, float t);
};

#endif // _MATHF_H_