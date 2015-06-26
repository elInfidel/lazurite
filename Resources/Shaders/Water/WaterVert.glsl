#version 410

layout(location = 0) in vec4 vertexPosition;
layout(location = 2) in vec2 vertexTexCoord;

uniform mat4 projectionView;
uniform float time;

uniform float height = 0.2f;
uniform float width = 0.2f;

out VertexData
{
  vec4 vertPosition;
  vec3 vertNormal;
  vec2 vertTexCoord;
} vData;

void main()
{
  vData.vertPosition = vertexPosition;
  vData.vertTexCoord = vertexTexCoord;

  vec4 pos = vertexPosition;
  pos.y = sin(width * pos.x + time) * cos(width * pos.y + time) * width;

  gl_Position = projectionView * pos;
}
