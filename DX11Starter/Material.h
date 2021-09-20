#pragma once

#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include "SimpleShader.h"

using namespace DirectX;

class Material
{
private:
	XMFLOAT4 colorTint;
	float shininess;
	ID3D11ShaderResourceView* srv;
	ID3D11SamplerState* sampler;
	SimplePixelShader* pixelShader;
	SimpleVertexShader* vertexShader;
	ID3D11ShaderResourceView* resourceView;
	ID3D11ShaderResourceView* roughness;
	ID3D11ShaderResourceView* metalness;

public:
	Material(XMFLOAT4 colorTint, float shininess, SimplePixelShader* pixelShader, SimpleVertexShader* vertexShader, ID3D11ShaderResourceView* srv, ID3D11SamplerState* sampler, ID3D11ShaderResourceView* roughness, ID3D11ShaderResourceView* metalness, ID3D11ShaderResourceView* normalMap = nullptr);
	~Material();

	XMFLOAT4 GetColorTint();
	float GetShininess();
	void SetColorTint(XMFLOAT4 colorTint);
	SimplePixelShader* GetPixelShader();
	SimpleVertexShader* GetVertexShader();
	ID3D11ShaderResourceView* GetShaderResourceView();
	ID3D11SamplerState* GetSamplerState();
	ID3D11ShaderResourceView* GetResourceView();
	ID3D11ShaderResourceView* GetRoughness();
	ID3D11ShaderResourceView* GetMetalness();
};

