#version 410

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vData
{
	vec4 vPosition;
  vec2 vTexCoord;
  vec3 vColor;
}vertices[];

out fData
{
	vec4 vPosition;
	vec3 vNormal;
	vec2 vTexCoord;
	vec3 vColor;
}frag;

void calculateNormal()
{
	// Implementation of Newell's method for surface normal generation
	vec3 U = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec3 V = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;

	frag.vNormal.x = (U.y * V.z) - (U.z * V.y);
	frag.vNormal.y = (U.z * V.x) - (U.x * V.z);
	frag.vNormal.z = (U.x * V.y) - (U.t * V.x);
}

void main()
{
	frag.vPosition = vertices[0].vPosition;
	frag.vTexCoord = vertices[0].vTexCoord;
	frag.vColor = vertices[0].vColor;

	calculateNormal();

	// Pass original vertex data through untouched
	gl_Position = gl_in[0].gl_Position;
    EmitVertex();

	gl_Position = gl_in[1].gl_Position;
    EmitVertex();

	gl_Position = gl_in[2].gl_Position;
    EmitVertex();
}
