#include "Material.h"

Material::Material(XMFLOAT4 colorTint, float shininess, SimplePixelShader* pixelShader, SimpleVertexShader* vertexShader, ID3D11ShaderResourceView* srv, ID3D11SamplerState* sampler, ID3D11ShaderResourceView* roughness, ID3D11ShaderResourceView* metalness, ID3D11ShaderResourceView* normalMap)
{
	this->colorTint = colorTint;
	this->shininess = shininess;
	this->pixelShader = pixelShader;
	this->vertexShader = vertexShader;
	this->srv = srv;
	this->sampler = sampler;
	this->resourceView = normalMap;
}

Material::~Material()
{
	//pixelShader->Release();
	//vertexShader->Release();
}

XMFLOAT4 Material::GetColorTint()
{
	return colorTint;
}

float Material::GetShininess()
{
	return shininess;
}

void Material::SetColorTint(XMFLOAT4 colorTint)
{
	this->colorTint = colorTint;
}

SimplePixelShader* Material::GetPixelShader()
{
	return pixelShader;
}

SimpleVertexShader* Material::GetVertexShader()
{
	return vertexShader;
}

ID3D11ShaderResourceView* Material::GetShaderResourceView()
{
	return srv;
}

ID3D11SamplerState* Material::GetSamplerState()
{
	return sampler;
}

ID3D11ShaderResourceView* Material::GetResourceView()
{
	return resourceView;
}

ID3D11ShaderResourceView* Material::GetRoughness()
{
	return roughness;
}

ID3D11ShaderResourceView* Material::GetMetalness()
{
	return metalness;
}