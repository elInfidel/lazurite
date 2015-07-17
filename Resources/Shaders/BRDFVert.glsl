#version 410

layout(location=0) in vec3 Position;
layout(location=2) in vec3 Normal;
layout(location=3) in vec3 Tangent;
layout(location=4) in vec3 BiTangent;
layout(location=7) in vec2 TexCoord;

uniform mat4 model = mat4(1);
uniform mat4 viewProjection;

uniform sampler2D height;

out struct vData
{
  vec3 position;
  vec3 normal;
  vec3 tangent;
  vec3 bitangent;
  vec2 texCoord;
} vertexData;

void main()
{
  // Passing vertex data through to fragment shader
  vertexData.position = Position;
  vertexData.normal = Normal;
  vertexData.tangent = Tangent;
  vertexData.bitangent = BiTangent;
  vertexData.texCoord = TexCoord;

  gl_Position = viewProjection * model * vec4(Position, 1);
}
