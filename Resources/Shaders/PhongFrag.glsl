#version 410

in vec4 vPosition;
in vec2 vTexCoord;
in vec4 vNormal;
in vec4 vTangent;
in vec4 vBiTangent;

out vec4 FragColor;

// Texture samplers
uniform sampler2D diffuse;
uniform sampler2D specular;
uniform sampler2D normal;

// Material Descriptions
uniform vec4 matA = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 matD = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 matS = vec4(0.0f, 0.0f, 0.0f, 0.0f);

uniform vec3 lightA = vec3(0.25f,0.25f,0.25f);
uniform vec3 lightD = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightS = vec3(1.0f, 1.0f, 1.0f);

uniform float specularPower = 128.0f;

uniform vec3 lightDir;
uniform vec3 cameraPos;

vec4 phongPerVertex()
{
	vec3 Ambient = matA.rgb * lightA; // ambient light
	
	float NdotL = max( 0.0f, dot( vNormal.xyz , normalize(lightDir)  )); // Lambert term
	vec3 Diffuse = matD.rgb * lightD * NdotL; // diffuse light for one light
	
	vec3 R = reflect( normalize(-lightDir), vNormal.xyz ); // reflected light vector
	vec3 E = normalize( cameraPos - vPosition.xyz ); // surface-to-eye vector
	
	float specTerm = pow( max( 0.0f, dot( R, E ) ), matS.a * specularPower ); // Specular term
	vec3 Specular = matS.rgb * lightS * specTerm * texture(specular, vTexCoord).rgb; // specular light for one light
	
	return vec4(Ambient + Diffuse + Specular, 1);
}

vec4 phongPerPixel()
{
	// Calculating normals
	mat3 TBN = mat3(normalize(vTangent), normalize(vBiTangent), normalize(vNormal));
	vec3 N = texture(normal, vTexCoord).rgb * 2 - 1;

	vec3 Ambient = matA.rgb * lightA; // ambient light
	
	float NdotL = max( 0.0f, dot( normalize(TBN * N) , normalize(-lightDir)  )); // Lambert term
	vec3 Diffuse = matD.rgb * lightD * NdotL; // diffuse light for one light
	
	vec3 R = reflect( normalize(lightDir), normalize(TBN * N) ); // reflected light vector
	vec3 E = normalize( cameraPos - vPosition.xyz ); // surface-to-eye vector
	
	float specTerm = pow( max( 0.0f, dot( R, E ) ), matS.a * specularPower ); // Specular term
	vec3 Specular = matS.rgb * lightS * specTerm * texture(specular, vTexCoord).rgb ; // specular light for one light
	
	return vec4(Ambient + Diffuse + Specular, 1);
}

void main()
{
	FragColor = phongPerPixel() * texture(diffuse, vTexCoord);
}
