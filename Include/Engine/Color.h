// ---------------------------------------------------------------------------
// Color.h
// A class representing an RGBA value
//
// Original author: <Liam Parker>
// Date created: 05/10/2014
// ---------------------------------------------------------------------------
#ifndef _COLOR_H_
#define _COLOR_H_

namespace lazurite
{
	class Color
	{
	public:
		Color();
		Color(float r, float g, float b);
		Color(float r, float g, float b, float a);
	
		~Color();
	
		float r, g, b, a;
	};
}

#endif // _COLOR_H_
