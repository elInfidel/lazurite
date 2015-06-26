#version 410

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 texCoord;

uniform sampler2D heightMap;
uniform mat4 projectionView;

out VertexData
{
  vec4 vertexPosition;
  vec3 vertexColor;
  vec3 normal;
  vec2 texCoord;
} vData;

float CalculateVertexHeight()
{
	return texture(heightMap, texCoord).r;
}

// Normal generation was achieved with the help of the following online source
// http://stackoverflow.com/questions/5281261/generating-a-normal-map-from-a-height-map
// Original code by kvark
void CalculateNormal()
{
	const vec2 size = vec2(2.0,0.0);
	const ivec3 off = ivec3(-1,0,1);

    vec4 height = texture(heightMap, texCoord);
    float s11 = height.x;
    float s01 = textureOffset(heightMap, texCoord, off.xy).x;
    float s21 = textureOffset(heightMap, texCoord, off.zy).x;
    float s10 = textureOffset(heightMap, texCoord, off.yx).x;
    float s12 = textureOffset(heightMap, texCoord, off.yz).x;
    vec3 va = normalize(vec3(size.x, s21-s11, -size.y));
	vec3 vb = normalize(vec3(size.y, s12-s10, size.x));
    vec4 bump = vec4( cross(va,vb), s11 );
	vData.normal = vec3(normalize(bump));
}

void main()
{
  vData.texCoord = texCoord;

  vec4 pos = vertexPosition;
  pos.y += CalculateVertexHeight();
  CalculateNormal();

  vData.vertexPosition = pos;

  gl_Position = projectionView * pos;
}
