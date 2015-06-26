#include "Light.h"


Light::Light()
{
	transform = new Transform();
	lightColor = vec3(0);
}


Light::~Light()
{
	delete transform;
}

vec3 Light::GetLightColor()
{
	return lightColor;
}

void Light::SetLightColor(vec3 newColor)
{
	lightColor = newColor;
}
