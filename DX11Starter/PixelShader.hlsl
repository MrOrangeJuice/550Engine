#include "ShaderIncludes.hlsli"

cbuffer ExternalData: register(b0)
{
	DirectionalLight light;
	DirectionalLight light2;
	DirectionalLight light3;
	PointLight pointLight;
	float3 ambientColor;
	float shininess;
	float3 cameraPosition;
}

Texture2D Albedo             : register(t0);
Texture2D RoughnessMap       : register(t1);
Texture2D MetalnessMap       : register(t2);
SamplerState samplerOptions  : register(s0);

// --------------------------------------------------------
// The entry point (main method) for our pixel shader
// 
// - Input is the data coming down the pipeline (defined by the struct)
// - Output is a single color (float4)
// - Has a special semantic (SV_TARGET), which means 
//    "put the output of this into the current render target"
// - Named "main" because that's the default the shader compiler looks for
// --------------------------------------------------------
float4 main(VertexToPixel input) : SV_TARGET
{
	float3 surfaceColor = pow(Albedo.Sample(samplerOptions, input.uv).rgb, 2.2f);

	float roughness = RoughnessMap.Sample(samplerOptions, input.uv).r;
	float metalness = MetalnessMap.Sample(samplerOptions, input.uv).r;
	float3 specularColor = lerp(F0_NON_METAL.rrr, surfaceColor.rgb, metalness);

	input.normal = normalize(input.normal);

	float3 normalLightDir = normalize(light.direction);
	float3 normalLightDir2 = normalize(light2.direction);
	float3 normalLightDir3 = normalize(light3.direction);
	float3 pointLightDir = normalize(input.worldPos - pointLight.position);

	/*
	float diffuse = Diffuse(input.normal, -normalLightDir);
	float diffuse2 = Diffuse(input.normal, -normalLightDir2);
	float diffuse3 = Diffuse(input.normal, -normalLightDir3);
	float diffusePoint = Diffuse(input.normal, -pointLightDir);
	*/

	float diffuse = DiffusePBR(input.normal, normalLightDir);
	float diffuse2 = DiffusePBR(input.normal, normalLightDir2);
	float diffuse3 = DiffusePBR(input.normal, normalLightDir3);
	float diffusePoint = DiffusePBR(input.normal, pointLightDir);

	float3 view = normalize(cameraPosition - input.worldPos);

	/*
	float phong = Phong(input.normal, normalLightDir, view, shininess);
	float phong2 = Phong(input.normal, normalLightDir2, view, shininess);
	float phong3 = Phong(input.normal, normalLightDir3, view, shininess);
	float phongPoint = Phong(input.normal, -pointLightDir, view, shininess);
	*/

	float phong = MicrofacetBRDF(input.normal, normalLightDir, view, roughness, metalness, specularColor);
	float phong2 = MicrofacetBRDF(input.normal, normalLightDir2, view, roughness, metalness, specularColor);
	float phong3 = MicrofacetBRDF(input.normal, normalLightDir3, view, roughness, metalness, specularColor);
	float phongPoint = MicrofacetBRDF(input.normal, pointLightDir, view, roughness, metalness, specularColor);

	// Calculate diffuse with energy conservation
	// (Reflected light doesn't get affected)
	float3 balancedDiff = DiffuseEnergyConserve(diffuse, phong, metalness);
	float3 balancedDiff2 = DiffuseEnergyConserve(diffuse2, phong2, metalness);
	float3 balancedDiff3 = DiffuseEnergyConserve(diffuse3, phong3, metalness);
	float3 balancedDiffPoint = DiffuseEnergyConserve(diffusePoint, phongPoint, metalness);

	// Combine the final diffuse and specular values for this light
	float3 total = (balancedDiff * surfaceColor + phong) * light.intensity * light.color;
	float3 total2 = (balancedDiff2 * surfaceColor + phong2) * light2.intensity * light2.color;
	float3 total3 = (balancedDiff3 * surfaceColor + phong3) * light3.intensity * light3.color;
	float3 totalPoint = (balancedDiffPoint * surfaceColor + phongPoint) * pointLight.intensity * pointLight.color;

	float3 finalColor = total + total2 + total3 + totalPoint + (ambientColor * surfaceColor);
	return float4(pow(finalColor, 1.0f / 2.2f), 1);

	// Just return the input color
	// - This color (like most values passing through the rasterizer) is 
	//   interpolated for each pixel between the corresponding vertices 
	//   of the triangle we're rendering
	//return input.color;
}