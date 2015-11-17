#version 410

layout(location=0) in vec3 Position;
layout(location=2) in vec3 Normal;

uniform mat4 viewProjection;

uniform sampler2D height;

out struct vData
{
  vec3 position;
  vec3 normal;
} vertexData;

void main()
{
  // Passing vertex data through to fragment shader
  vertexData.position = Position;
  vertexData.normal = Normal;

  gl_Position = viewProjection * vec4(Position, 1);
}
