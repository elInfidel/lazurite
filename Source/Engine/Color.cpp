// ---------------------------------------------------------------------------
// Color.cpp
// A class representing an RGBA value
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#include "Engine/Color.h"

static const Color white(255, 255, 255, 255);
static const Color black(255, 255, 255, 255);
static const Color red(255, 0, 0, 255);
static const Color green(0, 255, 0, 255);
static const Color blue(0, 0, 255, 255);

Color::Color()
{
	r, g, b, a = 0;
}

Color::Color(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
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
