// ---------------------------------------------------------------------------
// Color.cpp
// A class representing an RGBA value
//
// Original author: <Liam Parker>
// Date created: 05/10/2014
// ---------------------------------------------------------------------------
#include "Engine/Color.h"

namespace lazurite
{
	namespace color
	{
		static const Color White(255, 255, 255, 255);
		static const Color Black(0.0f, 0.0f, 0.0f, 255);
		static const Color Red(255, 0.0f, 0.0f, 255);
		static const Color Green(0.0f, 255, 0.0f, 255);
		static const Color Blue(0.0f, 0.0f, 255, 255);
	}
	
	Color::Color()
	{
		r, g, b, a = 0;
	}
	
	Color::Color(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 1.0f;
	}
	
	Color::Color(float r, float g, float b, float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	
	Color::~Color()
	{
	}
}