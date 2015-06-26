#version 410

in vec4 vPosition;
in vec2 vTexCoord;
in vec4 vNormal;
in vec4 vTangent;
in vec4 vBiTangent;

out vec4 FragColor;

uniform sampler2D diffuse;
uniform sampler2D specular;
uniform sampler2D normal;

uniform vec3 lightDir;

vec4 phong()
{

}

void main()
{
	mat3 TBN = mat3(normalize(vTangent), normalize(vBiTangent), normalize(vNormal));
	vec3 N = texture(normal, vTexCoord).xyz * 2 - 1;
	float d = max(0, dot(normalize(TBN * N), normalize(lightDir)));
	FragColor = texture(diffuse, vTexCoord);
	FragColor.rgb = FragColor.rgb * d;
}
