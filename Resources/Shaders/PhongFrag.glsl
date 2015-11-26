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

out vec4 fragColor;

void main()
{
	vec3 n = normalize(vertexData.n);
	vec3 l = normalize(vertexData.l);
	vec3 v = normalize(vertexData.v);

	vec3 r = reflect(l, n);

	vec3 diffuse = max(dot(n, -l), 0.0) * matD;
	vec3 specular = pow(max(dot(r, v), 0.0), specPow) * matS;


    fragColor = vec4(matA + diffuse + specular, 1.0f);
}
