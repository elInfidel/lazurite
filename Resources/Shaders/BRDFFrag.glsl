#version 410

// Material Descriptions
uniform vec4 matA = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 matD = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 matS = vec4(0.0f, 0.0f, 0.0f, 0.0f);

uniform vec3 lightA = vec3(0.25f,0.25f,0.25f);
uniform vec3 lightD = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightS = vec3(1.0f, 1.0f, 1.0f);

uniform float fresnelScale = 1.0f;
uniform float roughness = 0.0f;

uniform vec3 lightDir;
uniform vec3 cameraPos;

//uniform bool alphaTested = false;

const float e = 2.71828f;
const float pi = 3.14159f;

// Texture samplers
uniform sampler2D diffuse;
uniform sampler2D specular;
uniform sampler2D ambient;
uniform sampler2D normal;

in struct vData
{
  vec3 position;
  vec3 normal;
  vec3 tangent;
  vec3 bitangent;
  vec2 texCoord;
} vertexData;

out vec4 fragColor;

vec3 BRDF()
{
  // surface-to-eye vector
  vec3 E = normalize( cameraPos - vertexData.position.xyz );
  // Vertex normal
  //mat3 TBN = mat3(normalize(vertexData.tangent), normalize(vertexData.bitangent), normalize(vertexData.normal));
  //vec3 N = normalize(TBN * (texture(normal, vertexData.texCoord).rgb * 2 - 1));
  vec3 N = normalize(vertexData.normal);
  // Light direction Vector
  vec3 L = -lightDir;
  // Half Vector
  vec3 H = normalize(L + E);

  // AMBIENT TERM
	vec3 Ambient = matA.rgb * lightA.rgb * texture(ambient, vertexData.texCoord).rgb; // ambient light

  // DIFFUSE TERM
  float NdL = max( 0.0f, dot( N, L ) );
  float NdE = max( 0.0f, dot( N, E ) );
  float R2 = roughness * roughness;

  float A = 1.0f - 0.5f * (R2 / (R2 + 0.33f));
  float B = 0.45f * (R2 / (R2 + 0.09f));
  // CX = Max(0, cos(l,e))
  vec3 lightProjected = normalize( L - N * NdL );
  vec3 viewProjected = normalize( E - N * NdE);
  float CX = max( 0.0f, dot( lightProjected, viewProjected ) );
  // DX = sin(alpha) * tan(beta)
  float alpha = sin( max( acos( NdE ), acos( NdL ) ) );
  float beta = tan( min( acos( NdE ), acos( NdL ) ) );
  float DX = alpha * beta;
  // Calculate Oren-Nayar diffuse
  float OrenNayar = NdL * (A + B * CX * DX);
  vec3 Diffuse = matD.rgb * lightD * texture(diffuse, vertexData.texCoord).rgb * OrenNayar;

  // SPECULAR TERM
  // Beckman's Distribution Function D
  float NdH = max(dot( N, H), 0.0f);
  float NdH2 = NdH * NdH;
  float exponent = -(1f - NdH2) / (NdH2 * R2);
  float D = pow( e, exponent ) / (R2 * NdH2 * NdH2);
  // Fresnel Term F
  float HdE = dot( H, E );
  float F = mix( pow( 1f - HdE, 5f ), 1f, fresnelScale );
  // Geometric Attenuation Factor G
  float X = 2.0f * NdH / dot( E, H );
  float G = min(1, min(X * NdE, X * NdL));
  // Calculate Cook-Torrance
  float CookTorrance = max( (D*G*F) / (NdE * pi), 0.0f );
  vec3 Specular = matS.rgb * lightS.rgb * texture(specular, vertexData.texCoord).r * CookTorrance;

	return vec3(Ambient + Diffuse + Specular);
}

void main()
{
    fragColor = vec4(BRDF(), 1);
}
