#version 410

in struct vData
{
	vec3 n;
	vec3 l;
	vec3 v;
} vertexData;

// Material Descriptions
uniform vec3 matA = vec3(1.0f);
uniform vec3 matD = vec3(1.0f);
uniform vec3 matS = vec3(1.0f);

uniform vec3 lightA = vec3(0.25);
uniform vec3 lightD = vec3(1.0);
uniform vec3 lightS = vec3(1.0);

uniform float specPow = 128.0f;

uniform vec3 rimColor = vec3(0.5f, 0.5f, 0.5f);
uniform float rimPower = 28.0f;

out vec4 fragColor;

vec3 calculateRim(vec3 n, vec3 v);

void main()
{
	vec3 n = normalize(vertexData.n);
	vec3 l = -normalize(vertexData.l);
	vec3 v = normalize(vertexData.v);

	vec3 h = normalize(l + v);

	vec3 diffuse = max(dot(n, l), 0.0) * matD;
	vec3 specular = pow(max(dot(n, h), 0.0), specPow) * matS;

	vec3 rim = calculateRim(n, v);

    fragColor = vec4(matA + diffuse + specular + rim, 1.0f);
}

vec3 calculateRim(vec3 n, vec3 v)
{
	float f = 1.0f - dot(n, v);

	f = smoothstep(0.0f, 1.0f, f);

	f = pow(f, rimPower);

	return f * rimColor;
}
