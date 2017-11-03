#version 420 core

in struct vData
{
  vec3 normal;
  vec3 lightDir;
  vec3 viewDir;
} vertexData;

// Material Descriptions
uniform vec3 matAmbient = vec3(1.0f);
uniform vec3 matDiffuse = vec3(1.0f);
uniform vec3 matSpecular = vec3(1.0f);

uniform vec3 lightAmbient = vec3(0.25);
uniform vec3 lightDiffuse = vec3(1.0);
uniform vec3 lightSpecular = vec3(1.0);

uniform float specPow = 128.0f;

uniform vec3 rimColor = vec3(0.5f, 0.5f, 0.5f);
uniform float rimPower = 6.0f;

out vec4 fragColor;

vec3 calculateRim(vec3 n, vec3 v);

void main()
{
	vec3 normal = normalize(vertexData.normal);
	vec3 lightDir = normalize(vertexData.lightDir);
	vec3 viewDir = normalize(vertexData.viewDir);

	vec3 halfDir = normalize(lightDir + viewDir);

	vec3 diffuse = max(dot(normal, lightDir), 0.0) * matDiffuse;

	vec3 specular = pow(max(dot(normal, halfDir), 0.0), specPow) * matSpecular;

	vec3 rim = calculateRim(normal, viewDir);

    fragColor = vec4(matAmbient + diffuse + specular + rim, 1.0f);
}

vec3 calculateRim(vec3 n, vec3 v)
{
	float f = 1.0f - dot(n, v);

	f = smoothstep(0.0f, 1.0f, f);

	f = pow(f, rimPower);

	return f * rimColor;
}
