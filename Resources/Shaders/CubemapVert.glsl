#version 400

layout(location = 0) in vec3 position;

uniform mat4 pMat, vMat;
out vec3 texcoords;

void main ()
{
  texcoords = position;
  gl_Position = pMat * vMat * vec4 (position, 1.0);
}
