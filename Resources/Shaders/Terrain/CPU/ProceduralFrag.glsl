#version 410

uniform sampler2D heightMap;
uniform sampler2D grass;
uniform sampler2D rock;
uniform sampler2D snow;

uniform vec3 lightDir = vec3(0, -1, 0);
uniform vec3 lightColor = vec3(1, 1, 1);
uniform vec3 cameraPos;
uniform float specPow = 1;

in VertexData
{
  vec4 vertexPosition;
  vec3 vertexColor;
  vec3 normal;
  vec2 texCoord;
} vData;

out vec4 fragColor;

vec3 phong()
{
	float d = max(0, dot(normalize(vData.normal.xyz), lightDir));

	vec3 E = normalize(cameraPos - vData.vertexPosition.xyz);
	vec3 R = reflect(-lightDir, vData.normal.xyz);

	float s = max(0, dot( E, R));
	s = pow(s, specPow) * 0.0f;

	return lightColor * d + lightColor * s;
}

void main()
{
  vec2 scaledTexCoord = vData.texCoord * 50;

  if(vData.vertexPosition.y < 5.0f)
  {
    fragColor = texture(grass, scaledTexCoord) * vec4(phong(), 1);
  }
  else if(vData.vertexPosition.y < 18.0f)
  {
    fragColor = texture(rock, scaledTexCoord) * vec4(phong(), 1);
  }
  else if(vData.vertexPosition.y > 18.0f)
  {
    fragColor = texture(snow, scaledTexCoord) * vec4(phong(), 1);
  }
}
