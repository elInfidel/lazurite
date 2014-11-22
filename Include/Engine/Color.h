// ---------------------------------------------------------------------------
// Color.h
// A class representing an RGBA value
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#ifndef _COLOR_H_
#define _COLOR_H_

class Color
{
public:
	Color();
	Color(float r, float g, float b);
	Color(float r, float g, float b, float a);

	~Color();

private:
	float r, g, b, a;
};

#endif // _COLOR_H_
