#include "Sky.h"

Sky::Sky(Mesh* mesh, ID3D11SamplerState* samplerOptions, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11ShaderResourceView* cubeSRV, SimplePixelShader* skyPS, SimpleVertexShader* skyVS)
{
	this->mesh = mesh;
	this->samplerOptions = samplerOptions;
	this->cubeSRV = cubeSRV;
	this->skyPS = skyPS;
	this->skyVS = skyVS;

	// Rasterizer state
	D3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.FillMode = D3D11_FILL_SOLID;
	rastDesc.CullMode = D3D11_CULL_FRONT;

	device->CreateRasterizerState(&rastDesc, &rasterizerOptions);

	// Depth-Stencil State
	D3D11_DEPTH_STENCIL_DESC stencilDesc = {};
	stencilDesc.DepthEnable = true;
	stencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	device->CreateDepthStencilState(&stencilDesc, &comparisonType);
}

Sky::~Sky()
{
	comparisonType->Release();
	rasterizerOptions->Release();
}

void Sky::Draw(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context, Camera* camera)
{
	context->RSSetState(rasterizerOptions);
	context->OMSetDepthStencilState(comparisonType, 0);

	skyPS->SetShader();
	skyVS->SetShader();

	// Pixel shader
	skyPS->SetShaderResourceView("cubeMap", cubeSRV);
	skyPS->SetSamplerState("samplerOptions", samplerOptions);

	// Vertex Shader
	skyVS->SetMatrix4x4("view", camera->GetViewMatrix());
	skyVS->SetMatrix4x4("projection", camera->GetProjectionMatrix());
	skyVS->CopyAllBufferData();

	// Draw
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	vertexBufferVar = mesh->GetVertexBuffer();
	context->IASetVertexBuffers(0, 1, &vertexBufferVar, &stride, &offset);
	indexBufferVar = mesh->GetIndexBuffer();
	context->IASetIndexBuffer(indexBufferVar, DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(mesh->GetIndexCount(), 0, 0);

	// Reset rasterizer state
	context->RSSetState(0);
	context->OMSetDepthStencilState(0, 0);

}