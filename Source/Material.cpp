#include "Material.h"


Material::Material()
{
	properties.ambient = vec3(0.0f);
	properties.diffuse = vec3(0.0f);
	properties.specular = vec3(0.0f);
}


Material::~Material()
{

}
