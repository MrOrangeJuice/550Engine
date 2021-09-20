#include "ShaderIncludes.hlsli"

TextureCube cubeMap          : register(t0);
SamplerState samplerOptions  : register(s0);

float4 main(VertexToPixelSky input) : SV_TARGET
{
	return cubeMap.Sample(samplerOptions, input.sampleDir);
}