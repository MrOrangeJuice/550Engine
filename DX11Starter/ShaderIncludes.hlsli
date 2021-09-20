#ifndef __GGP_SHADER_INCLUDES__ // Each file needs a unique identifier here!
#define __GGP_SHADER_INCLUDES__

static const float F0_NON_METAL = 0.04f;
// Minimum roughness for when spec distribution function denominator goes to zero
static const float MIN_ROUGHNESS = 0.0000001f;
// 6 zeros after decimal
// Handy to have this as a constant
static const float PI = 3.14159265359f;


// Struct representing the data we're sending down the pipeline
// - Should match our pixel shader's input (hence the name: Vertex to Pixel)
// - At a minimum, we need a piece of data defined tagged as SV_POSITION
// - The name of the struct itself is unimportant, but should be descriptive
// - Each variable must have a semantic, which defines its usage
struct VertexToPixel
{
	// Data type
	//  |
	//  |   Name          Semantic
	//  |    |                |
	//  v    v                v
	float4 position		: SV_POSITION;	// XYZW position (System Value Position)
	float4 color		: COLOR;        // RGBA color
	float3 normal       : NORMAL;
	float3 worldPos     : POSITION;
	float2 uv           : TEXCOORD;
};

struct VertexToPixelNormalMap
{
	// Data type
	//  |
	//  |   Name          Semantic
	//  |    |                |
	//  v    v                v
	float4 position		: SV_POSITION;	// XYZW position (System Value Position)
	float4 color		: COLOR;        // RGBA color
	float3 normal       : NORMAL;
	float3 worldPos     : POSITION;
	float2 uv           : TEXCOORD;
	float3 tangent      : TANGENT;
};

struct VertexToPixelSky
{
	float4 position		: SV_POSITION;
	float3 sampleDir    : DIRECTION;
};

struct DirectionalLight
{
	float3 color;
	float intensity;
	float3 direction;
};

struct PointLight
{
	float3 color;
	float intensity;
	float3 position;
};

float Diffuse(float3 normal, float3 dirToLight)
{
	float dotProduct = dot(normal, dirToLight);
	dotProduct = saturate(dotProduct);
	return dotProduct;
}

float Phong(float3 normal, float3 incomingLight, float3 view, float shininess)
{
	float3 r = reflect(incomingLight, normal);

	return pow(saturate(dot(r, view)), shininess);
}

// Lambert diffuse BRDF - Same as the basic lighting diffuse calculation!
// - NOTE: this function assumes the vectors are already NORMALIZED!
float DiffusePBR(float3 normal, float3 dirToLight)
{ 
	return saturate(dot(normal, dirToLight));
} 
// Calculates diffuse amount based on energy conservation
//
// diffuse - Diffuse amount
// specular - Specular color (including light color)
// metalness - surface metalness amount
//
// Metals should have an albedo of (0,0,0)...mostly
// See slide 65: http://blog.selfshadow.com/publications/s2014-shading-course/hoffman/s2014_pbs_physics_math_slides.pdf
float3 DiffuseEnergyConserve(float diffuse, float3 specular, float metalness)
{ 
	return diffuse * ((1 - saturate(specular)) * (1 - metalness));
} 

// GGX (Trowbridge-Reitz)
//
// a - Roughness
// h - Half vector
// n - Normal
//  
// D(h, n) = a^2 / pi * ((n dot h)^2 * (a^2 - 1) + 1)^2 
float SpecDistribution(float3 n, float3 h, float roughness)
{ // Pre-calculations
	float NdotH = saturate(dot(n, h));
	float NdotH2 = NdotH * NdotH;
	float a = roughness * roughness;
	float a2 = max(a * a, MIN_ROUGHNESS); // Applied after remap!
	// ((n dot h)^2 * (a^2 - 1) + 1)
	float denomToSquare = NdotH2 * (a2 - 1) + 1;
	// Can go to zero if roughness is 0 and NdotH is 1
	// Final value
	return a2 / (PI * denomToSquare * denomToSquare);
} 

// Fresnel term - Schlick approx.
//  
// v - View vector
// h - Half vector
// f0 - Value when l = n (full specular color)
// 
// F(v,h,f0) = f0 + (1-f0)(1 - (v dot h))^5
float3 Fresnel(float3 v,   float3 h,   float3 f0)  
{ 
	// Pre-calculations
	float VdotH = saturate(dot(v, h));
	// Final value
	return f0 + (1 - f0) * pow(1 - VdotH, 5);
} 

// Geometric Shadowing - Schlick-GGX (based on Schlick-Beckmann)
// - k is remapped to a / 2, roughness remapped to (r+1)/2
// 
// n - Normal
// v - View vector
//
// G(l,v,h)
float GeometricShadowing(float3 n,   float3 v,   float3 h,   float roughness)
{ // End result of remapping:
	float k = pow(roughness + 1, 2) / 8.0f;
	float NdotV = saturate(dot(n, v));
	// Final value
	return NdotV / (NdotV * (1 - k) + k);
} 

// Microfacet BRDF (Specular)
// 
// f(l,v) = D(h)F(v,h)G(l,v,h) / 4(n dot l)(n dot v)
// - part of the denominator are canceled out by numerator (see below)
// 
// D() - Spec Dist - Trowbridge-Reitz (GGX)
// F() - Fresnel - Schlick approx
// G() - Geometric Shadowing - Schlick-GGX   
float3 MicrofacetBRDF(float3 n,   float3 l,   float3 v,   float roughness, float metalness, float3 specColor)
{ 
	// Other vectors
	float3 h = normalize(v + l); 
	// Grab various functions
	float D = SpecDistribution(n, h, roughness);
	float3 F = Fresnel(v, h, specColor);
	float G = GeometricShadowing(n, v, h, roughness) * GeometricShadowing(n, l, h, roughness);
	// Final formula
	// Denominator dot products partially canceled by G()!
	// See page 16: http://blog.selfshadow.com/publications/s2012-shading-course/hoffman/s2012_pbs_physics_math_notes.pdf
	return (D * F * G) / (4 * max(dot(n,v), dot(n,l)));
}

float ApplyToonRamp(float originalNdotL, Texture2D ramp, SamplerState clampSampler)
{
	return ramp.Sample(clampSampler, float2(originalNdotL, 0)).r;
}

#endif