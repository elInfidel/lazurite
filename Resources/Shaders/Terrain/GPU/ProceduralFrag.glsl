#version 410

in fData
{
	vec4 vPosition;
	vec3 vNormal;
	vec2 vTexCoord;
	vec3 vColor;
}frag;


out vec4 fragColor;

uniform vec3 lightDir = vec3(0, -1, 0);
uniform vec3 lightColor = vec3(1, 1, 1);
uniform vec3 cameraPos;
uniform float specPow = 1;

vec3 phong()
{
	float d = max(0, dot(normalize(frag.vNormal.xyz), lightDir));

	vec3 E = normalize(cameraPos - frag.vPosition.xyz);
	vec3 R = reflect(-lightDir, frag.vNormal.xyz);

	float s = max(0, dot( E, R));
	s = pow(s, specPow) * 0.0f;

	return lightColor * d + lightColor * s;
}

void main()
{
	if(frag.vPosition.y < -1.0f) discard;

	fragColor = vec4(phong() * frag.vColor, 1);
}
