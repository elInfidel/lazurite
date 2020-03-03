#version 420 core
out vec4 FragColor;
in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

// material parameters
layout(binding = 16) uniform sampler2D texture_diffuse;
layout(binding = 16) uniform sampler2D texture_normal;
layout(binding = 16) uniform sampler2D texture_metallic;
layout(binding = 16) uniform sampler2D texture_roughness;
layout(binding = 16) uniform sampler2D texture_ambientOcclusion;

// lights
uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];

uniform vec3 camPos;

const float PI=3.14159265359;

vec3 getNormalFromMap()
{
    vec3 tangentNormal=texture(texture_normal,TexCoords).xyz*2.-1.;
    
    vec3 Q1=dFdx(WorldPos);
    vec3 Q2=dFdy(WorldPos);
    vec2 st1=dFdx(TexCoords);
    vec2 st2=dFdy(TexCoords);
    
    vec3 N=normalize(Normal);
    vec3 T=normalize(Q1*st2.t-Q2*st1.t);
    vec3 B=-normalize(cross(N,T));
    mat3 TBN=mat3(T,B,N);
    
    return normalize(TBN*tangentNormal);
}

float DistributionGGX(vec3 N,vec3 H,float roughness)
{
    float a=roughness*roughness;
    float a2=a*a;
    float NdotH=max(dot(N,H),0.);
    float NdotH2=NdotH*NdotH;
    
    float nom=a2;
    float denom=(NdotH2*(a2-1.)+1.);
    denom=PI*denom*denom;
    
    return nom/denom;
}

float GeometrySchlickGGX(float NdotV,float roughness)
{
    float r=(roughness+1.);
    float k=(r*r)/8.;
    
    float nom=NdotV;
    float denom=NdotV*(1.-k)+k;
    
    return nom/denom;
}

float GeometrySmith(vec3 N,vec3 V,vec3 L,float roughness)
{
    float NdotV=max(dot(N,V),0.);
    float NdotL=max(dot(N,L),0.);
    float ggx2=GeometrySchlickGGX(NdotV,roughness);
    float ggx1=GeometrySchlickGGX(NdotL,roughness);
    
    return ggx1*ggx2;
}

vec3 fresnelSchlick(float cosTheta,vec3 F0)
{
    return F0+(1.-F0)*pow(1.-cosTheta,5.);
}

void main()
{

    vec4 albedoRaw = texture(texture_diffuse,TexCoords);

    // Very basic alpha handling for now..
    if(albedoRaw.a < 0.1) {
        discard;
    }

    vec3 albedo=pow(albedoRaw.rgb,vec3(2.2));
    float metallic=texture(texture_metallic,TexCoords).r;
    float roughness=texture(texture_roughness,TexCoords).r;
    float ao=texture(texture_ambientOcclusion,TexCoords).r;

    // For now we set the normal based on a normal texture being supplied.
    // To remove this branching condition moving forward, we should have a seperate shader
    // that uses vertex normals instead where no normal map was given.
    vec3 N;
    if(getNormalFromMap().r == 0) {
        N = getNormalFromMap();
    } else {
        N = Normal.rgb;
    }

    vec3 V=normalize(camPos-WorldPos);

    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)
    vec3 F0=vec3(.04);
    F0=mix(F0,albedo,metallic);
    
    // reflectance equation
    vec3 Lo=vec3(0.);
    for(int i=0;i<4;++i)
    {
        // calculate per-light radiance
        vec3 L=normalize(lightPositions[i]-WorldPos);
        vec3 H=normalize(V+L);
        float distance=length(lightPositions[i]-WorldPos);
        float attenuation=1./(distance*distance);
        vec3 radiance=lightColors[i]*attenuation;
        
        // Cook-Torrance BRDF
        float NDF=DistributionGGX(N,H,roughness);
        float G=GeometrySmith(N,V,L,roughness);
        vec3 F=fresnelSchlick(max(dot(H,V),0.),F0);
        
        vec3 nominator=NDF*G*F;
        float denominator=4*max(dot(N,V),0.)*max(dot(N,L),0.)+.001;// 0.001 to prevent divide by zero.
        vec3 specular=nominator/denominator;
        
        // kS is equal to Fresnel
        vec3 kS=F;
        
        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 kD=vec3(1.)-kS;
        
        // multiply kD by the inverse metalness such that only non-metals
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kD*=1.-metallic;
        
        // scale light by NdotL
        float NdotL=max(dot(N,L),0.);
        
        // add to outgoing radiance Lo
        Lo+=(kD*albedo/PI+specular)*radiance*NdotL;// note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    }
    
    // ambient lighting (note that the next IBL tutorial will replace
    // this ambient lighting with environment lighting).
    vec3 ambient=vec3(.03)*albedo*ao;
    
    vec3 color=ambient+Lo;
    
    // HDR tonemapping
    color=color/(color+vec3(1.));
    
    // gamma correct
    color=pow(color,vec3(1./2.2));
    
    // TODO: Use albedo alpha. We need to figure out sorting for transparent objects first
    FragColor=vec4(color, 1.);
}