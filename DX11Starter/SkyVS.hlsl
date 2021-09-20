#include "ShaderIncludes.hlsli"

cbuffer ExternalData: register(b0)
{
	matrix projection;
	matrix view;
}

struct VertexShaderInput
{
	// Data type
	//  |
	//  |   Name          Semantic
	//  |    |                |
	//  v    v                v
	float3 position		: POSITION;     // XYZ position
	float3 normal       : NORMAL;
	float2 uv           : TEXCOORD;
	float3 tangent      : TANGENT;
};


VertexToPixelSky main(VertexShaderInput input)
{
	// Set up output struct
	VertexToPixelSky output;

	matrix viewNoTranslation = view;
	viewNoTranslation._14 = 0;
	viewNoTranslation._24 = 0;
	viewNoTranslation._34 = 0;

	matrix pv = mul(projection, viewNoTranslation);
	output.position = mul(pv, float4(input.position, 1.0f));

	output.position.z = output.position.w;

	output.sampleDir = input.position;

	return output;
}