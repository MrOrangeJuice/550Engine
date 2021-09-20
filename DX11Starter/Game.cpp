#include "Game.h"
#include "Vertex.h"

// Needed for a helper function to read compiled shader files from the hard drive
#pragma comment(lib, "d3dcompiler.lib")
#include <d3dcompiler.h>

// For the DirectX Math library
using namespace DirectX;

// --------------------------------------------------------
// Constructor
//
// DXCore (base class) constructor will set up underlying fields.
// DirectX itself, and our window, are not ready yet!
//
// hInstance - the application's OS-level handle (unique ID)
// --------------------------------------------------------
Game::Game(HINSTANCE hInstance)
	: DXCore(
		hInstance,		   // The application's handle
		"DirectX Game",	   // Text for the window's title bar
		1280,			   // Width of the window's client area
		720,			   // Height of the window's client area
		true)			   // Show extra stats (fps) in title bar?
{

#if defined(DEBUG) || defined(_DEBUG)
	// Do we want a console window?  Probably only in debug mode
	CreateConsoleWindow(500, 120, 32, 120);
	printf("Console window created successfully.  Feel free to printf() here.\n");
#endif

}

// --------------------------------------------------------
// Destructor - Clean up anything our game has created:
//  - Release all DirectX objects created here
//  - Delete any objects to prevent memory leaks
// --------------------------------------------------------
Game::~Game()
{
	// Note: Since we're using smart pointers (ComPtr),
	// we don't need to explicitly clean up those DirectX objects
	// - If we weren't using smart pointers, we'd need
	//   to call Release() on each DirectX object created in Game
	delete mesh1;
	mesh1 = nullptr;
	delete mesh2;
	mesh2 = nullptr;
	delete mesh3;
	mesh3 = nullptr;
	delete mesh4;
	mesh4 = nullptr;
	delete mesh5;
	mesh5 = nullptr;
	delete mesh6;
	mesh6 = nullptr;

	for (int i = 0; i < entityList.size(); i++)
	{
		delete entityList[i];
		entityList[i] = nullptr;
	}
	delete camera;
	camera = nullptr;

	delete pixelShader;
	pixelShader = nullptr;
	delete vertexShader;
	vertexShader = nullptr;

	delete pixelShaderNormal;
	pixelShaderNormal = nullptr;
	delete vertexShaderNormal;
	vertexShaderNormal = nullptr;

	delete pixelShaderSky;
	pixelShaderSky = nullptr;
	delete vertexShaderSky;
	vertexShaderSky = nullptr;

	delete sky;
	sky = nullptr;

	delete material1;
	material1 = nullptr;
	delete material2;
	material2 = nullptr;
	delete material3;
	material3 = nullptr;
	delete material4;
	material4 = nullptr;
	delete material5;
	material5 = nullptr;
	delete material6;
	material6 = nullptr;
}

// --------------------------------------------------------
// Called once per program, after DirectX and the window
// are initialized but before the game loop.
// --------------------------------------------------------
void Game::Init()
{
	// Load textures
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/bronze_albedo.png").c_str(), 0, &bronzeAlbedo);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/bronze_metal").c_str(), 0, &bronzeMetal);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/bronze_normals.png").c_str(), 0, &bronzeNormals);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/bronze_roughness.png").c_str(), 0, &bronzeRoughness);

	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/cobblestone_albedo.png").c_str(), 0, &cobblestoneAlbedo);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/cobblestone_metal").c_str(), 0, &cobblestoneMetal);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/cobblestone_normals.png").c_str(), 0, &cobblestoneNormals);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/cobblestone_roughness.png").c_str(), 0, &cobblestoneRoughness);

	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/floor_albedo.png").c_str(), 0, &floorAlbedo);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/floor_metal").c_str(), 0, &floorMetal);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/floor_normals.png").c_str(), 0, &floorNormals);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/floor_roughness.png").c_str(), 0, &floorRoughness);

	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/paint_albedo.png").c_str(), 0, &paintAlbedo);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/paint_metal").c_str(), 0, &paintMetal);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/paint_normals.png").c_str(), 0, &paintNormals);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/paint_roughness.png").c_str(), 0, &paintRoughness);

	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/scratched_albedo.png").c_str(), 0, &scratchedAlbedo);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/scratched_metal").c_str(), 0, &scratchedMetal);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/scratched_normals.png").c_str(), 0, &scratchedNormals);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/scratched_roughness.png").c_str(), 0, &scratchedRoughness);



	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/ApricotDiffuse.png").c_str(), 0, &apricotAlbedo);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/ApricotNormal.png").c_str(), 0, &apricotNormals);

	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/Apple_BaseColor.png").c_str(), 0, &appleAlbedo);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/Apple_Normal.png").c_str(), 0, &appleNormals);

	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/Orange_BaseColor.png").c_str(), 0, &orangeAlbedo);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/Orange_Normal.png").c_str(), 0, &orangeNormals);

	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/Banana_BaseColor.png").c_str(), 0, &bananaAlbedo);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/Banana_Normal.png").c_str(), 0, &bananaNormals);

	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/pear_diffuse.jpg").c_str(), 0, &pearAlbedo);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/pear_normal_map.jpg").c_str(), 0, &pearNormals);

	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/LegsTexture.jpg").c_str(), 0, &tableAlbedo);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/LegsNorm.jpg").c_str(), 0, &tableNormals);


	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/toonRamp1.png").c_str(), 0, &toonRamp);
	CreateWICTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/toonRampSepcular.png").c_str(), 0, &toonRampSpecular);

	CreateDDSTextureFromFile(device.Get(), context.Get(), GetFullPathTo_Wide(L"../../Assets/Textures/SunnyCubeMap.dds").c_str(), 0, &skyBox);

	D3D11_SAMPLER_DESC sampleDesc = {};
	sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampleDesc.MaxAnisotropy = 8;
	sampleDesc.MaxLOD = D3D11_FLOAT32_MAX;
	
	device->CreateSamplerState(&sampleDesc, &sampler);

	sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

	device->CreateSamplerState(&sampleDesc, &clampSampler);

	// Helper methods for loading shaders, creating some basic
	// geometry to draw and some simple camera matrices.
	//  - You'll be expanding and/or replacing these later
	LoadShaders();
	CreateBasicGeometry();

	camera = new Camera(DirectX::XMFLOAT3(0,2,-20), (float)this->width / this->height);

	directionalLight.color = XMFLOAT3(0.2f, 0.2f, 1.0f);
	directionalLight.intensity = 1.0f;
	directionalLight.direction = XMFLOAT3(1.0f, -1.0f, 0.0f);

	directionalLight2.color = XMFLOAT3(0.2f, 1.0f, 0.2f);
	directionalLight2.intensity = 1.0f;
	directionalLight2.direction = XMFLOAT3(-1.0f, 1.0f, 0.0f);

	directionalLight3.color = XMFLOAT3(1.0f, 0.2f, 0.2f);
	directionalLight3.intensity = 1.0f;
	directionalLight3.direction = XMFLOAT3(-1.0f, -1.0f, 0.0f);

	pointLight.color = XMFLOAT3(0.2f, 1.0f, 1.0f);
	pointLight.intensity = 5.0f;
	pointLight.position = XMFLOAT3(0.0f, -5.0f, 0.0f);

	ambientColor = XMFLOAT3(0.05f, 0.05f, 0.1f);

	
	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

// --------------------------------------------------------
// Loads shaders from compiled shader object (.cso) files
// and also created the Input Layout that describes our 
// vertex data to the rendering pipeline. 
// - Input Layout creation is done here because it must 
//    be verified against vertex shader byte code
// - We'll have that byte code already loaded below
// --------------------------------------------------------
void Game::LoadShaders()
{
	vertexShader = new SimpleVertexShader(device.Get(), context.Get(), GetFullPathTo_Wide(L"VertexShader.cso").c_str());
	pixelShader = new SimplePixelShader(device.Get(), context.Get(), GetFullPathTo_Wide(L"PixelShader.cso").c_str());
	vertexShaderNormal = new SimpleVertexShader(device.Get(), context.Get(), GetFullPathTo_Wide(L"NormalMapVS.cso").c_str());
	pixelShaderNormal = new SimplePixelShader(device.Get(), context.Get(), GetFullPathTo_Wide(L"NormalMapPS.cso").c_str());
	pixelShaderSky = new SimplePixelShader(device.Get(), context.Get(), GetFullPathTo_Wide(L"SkyPS.cso").c_str());
	vertexShaderSky = new SimpleVertexShader(device.Get(), context.Get(), GetFullPathTo_Wide(L"SkyVS.cso").c_str());
}



// --------------------------------------------------------
// Creates the geometry we're going to draw - a single triangle for now
// --------------------------------------------------------
void Game::CreateBasicGeometry()
{
	// Create some temporary variables to represent colors
	// - Not necessary, just makes things more readable
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	// Create vertices
	Vertex vertices[] =
	{
		{ XMFLOAT3(+0.6f, +0.2f, +0.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
		{ XMFLOAT3(+0.8f, -0.2f, +0.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
		{ XMFLOAT3(+0.4f, -0.2f, +0.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
	};

	Vertex vertices2[] =
	{
		{ XMFLOAT3(-0.3f, +0.3f, +0.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
		{ XMFLOAT3(+0.3f, +0.3f, +0.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
		{ XMFLOAT3(+0.3f, -0.3f, +0.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
		{ XMFLOAT3(-0.3f, -0.3f, +0.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) }
	};

	Vertex vertices3[] =
	{
		{ XMFLOAT3(-0.5f, +0.5f, +0.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
		{ XMFLOAT3(+0.5f, +0.8f, +0.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
		{ XMFLOAT3(+0.5f, -0.5f, +0.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) },
		{ XMFLOAT3(-0.5f, -0.8f, +0.0f), XMFLOAT3(0,0,-1), XMFLOAT2(0,0) }
	};

	// Set up the indices
	unsigned int indices[] = { 0, 1, 2 };
	unsigned int indices2[] = { 0, 1, 2, 0, 2, 3 };
	unsigned int indices3[] = { 0, 1, 2, 0, 2, 3 };

	// Create meshes
	mesh1 = new Mesh(GetFullPathTo("../../Assets/Models/Apricot.obj").c_str(), device.Get());
	mesh2 = new Mesh(GetFullPathTo("../../Assets/Models/Apple.obj").c_str(), device.Get());
	mesh3 = new Mesh(GetFullPathTo("../../Assets/Models/Orange.obj").c_str(), device.Get());
	mesh4 = new Mesh(GetFullPathTo("../../Assets/Models/Banana.obj").c_str(), device.Get());
	mesh5 = new Mesh(GetFullPathTo("../../Assets/Models/pear.obj").c_str(), device.Get());
	mesh6 = new Mesh(GetFullPathTo("../../Assets/Models/Desk.obj").c_str(), device.Get());

	skyMesh = mesh2;

	// Create materials
	material1 = new Material(XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f), 160.0f, pixelShaderNormal, vertexShaderNormal, apricotAlbedo, sampler, bronzeRoughness, bronzeMetal, apricotNormals);
	material2 = new Material(XMFLOAT4(0.5f, 1.0f, 0.5f, 1.0f), 160.0f, pixelShaderNormal, vertexShaderNormal, appleAlbedo, sampler, cobblestoneRoughness, cobblestoneMetal, appleNormals);
	material3 = new Material(XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f), 160.0f, pixelShaderNormal, vertexShaderNormal, orangeAlbedo, sampler, floorRoughness, floorMetal, orangeNormals);
	material4 = new Material(XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f), 160.0f, pixelShaderNormal, vertexShaderNormal, bananaAlbedo, sampler, paintRoughness, paintMetal, bananaNormals);
	material5 = new Material(XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f), 160.0f, pixelShaderNormal, vertexShaderNormal, pearAlbedo, sampler, scratchedRoughness, scratchedMetal, pearNormals);
	material6 = new Material(XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f), 160.0f, pixelShaderNormal, vertexShaderNormal, tableAlbedo, sampler, scratchedRoughness, scratchedMetal, tableNormals);

	// Create entities
	entity1 = new Entity(mesh1, material1);
	entity2 = new Entity(mesh2, material2);
	entity3 = new Entity(mesh3, material3);
	entity4 = new Entity(mesh4, material4);
	entity5 = new Entity(mesh5, material5);
	entity6 = new Entity(mesh6, material6);

	// Move and scale entities
	entity1->GetTransform()->MoveAbsolute(10.0f, 0.0f, 0.0f);
	entity2->GetTransform()->Scale(0.05f, 0.05f, 0.05f);
	entity2->GetTransform()->MoveAbsolute(5.0f, 2.0f, 0.0f);
	entity3->GetTransform()->Scale(0.05f, 0.05f, 0.05f);
	entity3->GetTransform()->MoveAbsolute(0.0f, 2.0f, 0.0f);
	entity4->GetTransform()->Scale(0.05f, 0.05f, 0.05f);
	entity4->GetTransform()->MoveAbsolute(-5.0f, 2.0f, 0.0f);
	entity5->GetTransform()->MoveAbsolute(-10.0f, 2.0f, 0.0f);
	entity6->GetTransform()->MoveAbsolute(0.0f, -5.0f, 8.0f);
	entity6->GetTransform()->Scale(0.1f, 0.1f, 0.1f);

	entityList.push_back(entity1);
	entityList.push_back(entity2);
	entityList.push_back(entity3);
	entityList.push_back(entity4);
	entityList.push_back(entity5);
	entityList.push_back(entity6);

	sky = new Sky(skyMesh, sampler, device, skyBox, pixelShaderSky, vertexShaderSky);
}


// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void Game::OnResize()
{
	// Handle base-level DX resize stuff
	DXCore::OnResize();

	if (camera != nullptr)
	{
		camera->UpdateProjectionMatrix((float)this->width / this->height);
	}
}

// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void Game::Update(float deltaTime, float totalTime)
{
	// Quit if the escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();
	/*
	if (GetAsyncKeyState('W') & 0x8000)
	{
		entity1->GetTransform()->MoveAbsolute(0.0f, 0.0001f, 0.0f);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		entity1->GetTransform()->MoveAbsolute(0.0f, -0.0001f, 0.0f);
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		entity1->GetTransform()->MoveAbsolute(-0.0001f, 0.0f, 0.0f);
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		entity1->GetTransform()->MoveAbsolute(0.0001f, 0.0f, 0.0f);
	}
	*/

	entity1->GetTransform()->Rotate(0.0f, 0.1f * deltaTime, 0.0f);
	entity2->GetTransform()->Rotate(0.0f, 0.1f * deltaTime, 0.0f);
	entity3->GetTransform()->Rotate(0.0f, 0.1f * deltaTime, 0.0f);
	entity4->GetTransform()->Rotate(0.0f, 0.1f * deltaTime, 0.0f);
	entity5->GetTransform()->Rotate(0.0f, 0.1f * deltaTime, 0.0f);

	/*
	entity2->GetTransform()->MoveAbsolute(0.1f * deltaTime, 0.0f, 0.0f);
	entity3->GetTransform()->Rotate(0.1f * deltaTime, 0.1f * deltaTime, 0.1f * deltaTime);
	entity4->GetTransform()->MoveAbsolute(-0.1f * deltaTime, -0.1f * deltaTime, 0.0f);
	entity5->GetTransform()->Rotate(0.2f * deltaTime, 0.2f * deltaTime, 0.2f * deltaTime);
	*/

	// Update camera
	camera->Update(deltaTime, this->hWnd);
}

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void Game::Draw(float deltaTime, float totalTime)
{

	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };

	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of Draw (before drawing *anything*)
	context->ClearRenderTargetView(backBufferRTV.Get(), color);
	context->ClearDepthStencilView(
		depthStencilView.Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	for (Entity* entity : entityList)
	{
		SimplePixelShader* entityPixelShader = entity->GetMaterial()->GetPixelShader();
		entityPixelShader->SetShader();

		// Set lighting data
		entityPixelShader->SetData(
			"light",
			&directionalLight,
			sizeof(DirectionalLight));

		entityPixelShader->SetData(
			"light2",
			&directionalLight2,
			sizeof(DirectionalLight));

		entityPixelShader->SetData(
			"light3",
			&directionalLight3,
			sizeof(DirectionalLight));

		entityPixelShader->SetData(
			"pointLight",
			&pointLight,
			sizeof(PointLight));

		// Set texture data
		entityPixelShader->SetFloat3("ambientColor", ambientColor);
		entityPixelShader->SetFloat("shininess", entity->GetMaterial()->GetShininess());
		entityPixelShader->SetFloat3("cameraPosition", camera->GetTransform().GetPosition());
		entityPixelShader->SetShaderResourceView("Albedo", entity->GetMaterial()->GetShaderResourceView());
		if (entity->GetMaterial()->GetResourceView() != nullptr) entityPixelShader->SetShaderResourceView("normalMap", entity->GetMaterial()->GetResourceView());
		entityPixelShader->SetShaderResourceView("RoughnessMap", entity->GetMaterial()->GetRoughness());
		entityPixelShader->SetShaderResourceView("MetalnessMap", entity->GetMaterial()->GetMetalness());
		entityPixelShader->SetShaderResourceView("toonRamp", toonRamp);
		entityPixelShader->SetShaderResourceView("toonRampSpecular", toonRampSpecular);

		entityPixelShader->CopyAllBufferData();

		entityPixelShader->SetSamplerState("samplerOptions", entity->GetMaterial()->GetSamplerState());
		entityPixelShader->SetSamplerState("clampSampler", clampSampler);

		// Set vertex shader
		SimpleVertexShader* entityVertexShader = entity->GetMaterial()->GetVertexShader();
		entityVertexShader->SetShader();
		entityVertexShader->SetMatrix4x4("world", entity->GetTransform()->GetWorldMatrix());
		entityVertexShader->SetMatrix4x4("view", camera->GetViewMatrix());
		entityVertexShader->SetMatrix4x4("projection", camera->GetProjectionMatrix());
		entityVertexShader->SetFloat4("colorTint", entity->GetMaterial()->GetColorTint());

		vertexBufferVar = entity->GetMesh()->GetVertexBuffer();
		context->IASetVertexBuffers(0, 1, &vertexBufferVar, &stride, &offset);
		context->IASetIndexBuffer(entity->GetMesh()->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

		entityVertexShader->CopyAllBufferData();

		context->DrawIndexed(
			entity->GetMesh()->GetIndexCount(),     // The number of indices to use (we could draw a subset if we wanted)
			0,     // Offset to the first index we want to use
			0);    // Offset to add to each index when looking up vertices

	}

	sky->Draw(context, camera);

	// Present the back buffer to the user
	//  - Puts the final frame we're drawing into the window so the user can see it
	//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
	swapChain->Present(0, 0);

	// Due to the usage of a more sophisticated swap chain,
	// the render target must be re-bound after every call to Present()
	context->OMSetRenderTargets(1, backBufferRTV.GetAddressOf(), depthStencilView.Get());
}