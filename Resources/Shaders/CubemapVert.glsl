#version 400

layout(location = 0) in vec3 position;

uniform mat4 P, V;
out vec3 texcoords;

void main ()
{
  texcoords = position;
  gl_Position = P * V * vec4 (position, 1.0);
}
