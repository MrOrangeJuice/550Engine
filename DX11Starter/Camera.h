#pragma once
#include <Windows.h>
#include <DirectXMath.h>
#include "Transform.h"

class Camera
{
private:
	Transform transform;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
	POINT prevMousePos;
public:
	Camera(DirectX::XMFLOAT3 initialPosition, float aspectRatio);

	void UpdateProjectionMatrix(float aspectRatio);
	void UpdateViewMatrix();
	void Update(float dt, HWND windowHandle);

	DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjectionMatrix();
	Transform GetTransform();
};