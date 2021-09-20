#pragma once
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include "SimpleShader.h"
#include "Mesh.h"
#include "Camera.h"
#include <wrl/client.h> // Used for ComPtr - a smart pointer for COM objects

using namespace DirectX;

class Sky
{
private:
	ID3D11SamplerState* samplerOptions;
	ID3D11ShaderResourceView* cubeSRV;
	ID3D11DepthStencilState* comparisonType;
	ID3D11RasterizerState* rasterizerOptions;
	Mesh* mesh;
	SimplePixelShader* skyPS;
	SimpleVertexShader* skyVS;
	ID3D11Buffer* vertexBufferVar;
	ID3D11Buffer* indexBufferVar;
public:
	Sky(Mesh* mesh, ID3D11SamplerState* samplerOptions, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11ShaderResourceView* cubeSRV, SimplePixelShader* skyPS, SimpleVertexShader* skyVS);
	~Sky();
	void Draw(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context, Camera* camera);
};

