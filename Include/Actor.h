// ---------------------------------------------------------------------------
// Actor.h
// A base object for things represented in the game
//
// Original author: <Liam Parker>
// Date created: 02/01/2015
// ---------------------------------------------------------------------------
#ifndef _ACTOR_H_
#define _ACTOR_H_
#include "Math/Vector3.h"

using namespace lazmath;

class Actor
{
public:
	Actor();
	~Actor();

	inline Vector3& GetPosition() { return position; }
	Vector3& GetRotation() { return rotation; }

	 virtual void Update() = 0;
	 virtual void Draw() = 0;

protected:
	Vector3 position;
	Vector3 rotation;
	int width;
	int height;
	int bpp;
};

#endif // _ACTOR_H_