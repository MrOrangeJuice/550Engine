#pragma once

#include "DXCore.h"
#include "Mesh.h"
#include "Entity.h"
#include "Camera.h"
#include "Material.h"
#include "Lights.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#include "Sky.h"
#include <DirectXMath.h>
#include <wrl/client.h> // Used for ComPtr - a smart pointer for COM objects

class Game 
	: public DXCore
{

public:
	Game(HINSTANCE hInstance);
	~Game();

	// Overridden setup and game loop methods, which
	// will be called automatically
	void Init();
	void OnResize();
	void Update(float deltaTime, float totalTime);
	void Draw(float deltaTime, float totalTime);

private:

	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadShaders(); 
	void CreateBasicGeometry();

	// Make meshes
	Mesh* mesh1;
	Mesh* mesh2;
	Mesh* mesh3;
	Mesh* mesh4;
	Mesh* mesh5;
	Mesh* mesh6;

	// Make entities
	Entity* entity1;
	Entity* entity2;
	Entity* entity3;
	Entity* entity4;
	Entity* entity5;
	Entity* entity6;

	std::vector<Entity*> entityList;

	// Make materials
	Material* material1;
	Material* material2;
	Material* material3;
	Material* material4;
	Material* material5;
	Material* material6;

	// Camera
	Camera* camera;

	// Vertex Buffer Container
	ID3D11Buffer* vertexBufferVar;

	DirectionalLight directionalLight;
	DirectionalLight directionalLight2;
	DirectionalLight directionalLight3;
	PointLight pointLight;
	XMFLOAT3 ambientColor;

	
	// Note the usage of ComPtr below
	//  - This is a smart pointer for objects that abide by the
	//    Component Object Model, which DirectX objects do
	//  - More info here: https://github.com/Microsoft/DirectXTK/wiki/ComPtr

	// Buffers to hold actual geometry data
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
	
	// Shaders and shader-related constructs
	SimplePixelShader* pixelShader;
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShaderNormal;
	SimpleVertexShader* vertexShaderNormal;
	SimplePixelShader* pixelShaderSky;
	SimpleVertexShader* vertexShaderSky;

	// Texture stuff
	ID3D11ShaderResourceView* bronzeAlbedo;
	ID3D11ShaderResourceView* bronzeMetal;
	ID3D11ShaderResourceView* bronzeNormals;
	ID3D11ShaderResourceView* bronzeRoughness;

	ID3D11ShaderResourceView* cobblestoneAlbedo;
	ID3D11ShaderResourceView* cobblestoneMetal;
	ID3D11ShaderResourceView* cobblestoneNormals;
	ID3D11ShaderResourceView* cobblestoneRoughness;

	ID3D11ShaderResourceView* floorAlbedo;
	ID3D11ShaderResourceView* floorMetal;
	ID3D11ShaderResourceView* floorNormals;
	ID3D11ShaderResourceView* floorRoughness;

	ID3D11ShaderResourceView* paintAlbedo;
	ID3D11ShaderResourceView* paintMetal;
	ID3D11ShaderResourceView* paintNormals;
	ID3D11ShaderResourceView* paintRoughness;

	ID3D11ShaderResourceView* scratchedAlbedo;
	ID3D11ShaderResourceView* scratchedMetal;
	ID3D11ShaderResourceView* scratchedNormals;
	ID3D11ShaderResourceView* scratchedRoughness;

	ID3D11ShaderResourceView* apricotAlbedo;
	ID3D11ShaderResourceView* apricotNormals;

	ID3D11ShaderResourceView* appleAlbedo;
	ID3D11ShaderResourceView* appleNormals;

	ID3D11ShaderResourceView* orangeAlbedo;
	ID3D11ShaderResourceView* orangeNormals;

	ID3D11ShaderResourceView* bananaAlbedo;
	ID3D11ShaderResourceView* bananaNormals;

	ID3D11ShaderResourceView* pearAlbedo;
	ID3D11ShaderResourceView* pearNormals;

	ID3D11ShaderResourceView* tableAlbedo;
	ID3D11ShaderResourceView* tableNormals;

	ID3D11ShaderResourceView* toonRamp;
	ID3D11ShaderResourceView* toonRampSpecular;

	ID3D11ShaderResourceView* skyBox;

	// Skybox stuff
	Sky* sky;
	Mesh* skyMesh;

	ID3D11SamplerState* sampler;
	ID3D11SamplerState* clampSampler;

	// Game variables
	float vsp;
	float grv;
	boolean prevJump;
	boolean canJump;
	boolean keyJump;
	boolean keyJumpReleased;
};

