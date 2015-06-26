#version 410

in vec4 vNormal;
in vec4 vPosition;

out vec4 fragColor;

// Material Descriptions
uniform vec3 matA = vec3(0.4f, 0.4f, 0.8f);
uniform vec3 matD = vec3(0.4f, 0.4f, 0.8f);
uniform vec3 matS = vec3(0.4f, 0.4f, 0.8f);

uniform vec3 lightA = vec3(0.25f,0.25f,0.25f);
uniform vec3 lightD = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightS = vec3(1.0f, 1.0f, 1.0f);

uniform float specularPower = 128.0f;

uniform vec3 lightDir;
uniform vec3 cameraPos;

void main()
{
	vec3 Ambient = matA * lightA; // ambient light
	
	float NdotL = max( 0.0f, dot( vNormal.xyz , normalize(lightDir)  )); // Lambert term
	vec3 Diffuse = matD * lightD * NdotL; // diffuse light for one light
	
	vec3 R = reflect( normalize(-lightDir), vNormal.xyz ); // reflected light vector
	vec3 E = normalize( cameraPos - vPosition.xyz ); // surface-to-eye vector
	
	float specTerm = pow( max( 0.0f, dot( R, E ) ), specularPower ); // Specular term
	vec3 Specular = matS * lightS * specTerm; // specular light for one light
	
	fragColor = vec4(Ambient + Diffuse + Specular, 1);
}