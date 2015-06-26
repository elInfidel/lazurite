#version 410

in VertexData
{
  vec4 vertPosition;
  vec3 vertNormal;
  vec2 vertTexCoord;
} vData;

uniform vec3 lightDir = vec3(0, -1, 0);
uniform vec3 lightColor = vec3(1, 1, 1);
uniform vec3 cameraPos;
uniform float specPow = 1;

out vec4 fragColor;

vec3 phong()
{
	float d = max(0, dot(normalize(vec3(0,1,0)), lightDir));

	vec3 E = normalize(cameraPos - vData.vertPosition.xyz);
	vec3 R = reflect(-lightDir, vData.vertNormal.xyz);

	float s = max(0, dot( E, R));
	s = pow(s, specPow) * 0.0f;

	return lightColor * d + lightColor * s;
}

void main()
{
  fragColor = vec4(vec3(51.0f / 255, 102.0f / 255, 255) * phong(), 1);
}
