#version 400

smooth in vec4 vertColour;
in vec2 UV;

out vec4 outputColour;

uniform sampler2D myTextureSampler;

void main()
{
	outputColour = texture2D(myTextureSampler, UV).rgba * vertColour;

	//Simple alternative to transparency
	if(texture2D(myTextureSampler, UV).a < 1.0f)
		discard;
}
