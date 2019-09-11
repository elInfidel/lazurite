#include "rendering/Material.h"


Material::Material()
{
	_program = nullptr;
	properties.ambient = vec3(0.0f);
	properties.diffuse = vec3(0.0f);
	properties.specular = vec3(0.0f);
	properties.fresnel = 0.0f;
	properties.roughness = 0.0f;
}

Material::~Material()
{
	if (_program)
	{
		delete _program;
	}
}
