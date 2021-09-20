#include "Camera.h"

Camera::Camera(DirectX::XMFLOAT3 initialPosition, float aspectRatio)
{
	// Set initial position
	transform.SetPosition(initialPosition.x, initialPosition.y, initialPosition.z);

	UpdateViewMatrix();
	UpdateProjectionMatrix(aspectRatio);
}

void Camera::UpdateProjectionMatrix(float aspectRatio)
{
	// Create new projection matrix and store it
	DirectX::XMMATRIX projMatrix = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, aspectRatio, 0.01f, 1000.0f);
	DirectX::XMStoreFloat4x4(&projection, projMatrix);
}

void Camera::UpdateViewMatrix()
{
	// Set position, direction, and up vector for view matrix
	/*
	DirectX::XMFLOAT3 position = transform.GetPosition();
	DirectX::XMVECTOR directionVector = DirectX::XMVectorSet(position.x, position.y, position.z, 0);
	DirectX::XMVECTOR directionQuat = DirectX::XMQuaternionRotationRollPitchYaw(transform.GetPitchYawRoll().x, transform.GetPitchYawRoll().y, transform.GetPitchYawRoll().z);
	DirectX::XMVECTOR directionTotal = DirectX::XMVector3Rotate(DirectX::XMVectorSet(0, 0, 1, 0), DirectX::XMQuaternionRotationRollPitchYawFromVector(directionQuat));

	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookToLH(DirectX::XMLoadFloat3(&position), directionTotal, DirectX::XMVectorSet(0, 1, 0, 0));
	DirectX::XMStoreFloat4x4(&view, viewMatrix);
	*/

	DirectX::XMFLOAT3 position = transform.GetPosition();
	XMFLOAT3 rot = transform.GetPitchYawRoll();
	XMVECTOR dir = XMVector3Rotate(XMVectorSet(0, 0, 1, 0), XMQuaternionRotationRollPitchYawFromVector(XMLoadFloat3(&rot)));

	XMMATRIX viewMat = DirectX::XMMatrixLookToLH(
		DirectX::XMLoadFloat3(&position),
		dir,
		XMVectorSet(0, 1, 0, 0));

	XMStoreFloat4x4(&view, viewMat);
}

void Camera::Update(float dt, HWND windowHandle)
{
	// Get input
	float speed = 4.0f * dt;

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
		speed *= 2;
	}
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
		speed *= 0.5;
	}
	if (GetAsyncKeyState('W') & 0x8000) {
		transform.MoveRelative(0, 0, speed);
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		transform.MoveRelative(0, 0, -speed);
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		transform.MoveRelative(-speed, 0, 0);
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		transform.MoveRelative(speed, 0, 0);
	}
	if (GetAsyncKeyState('X') & 0x8000) {
		transform.MoveAbsolute(0, -speed, 0);
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		transform.MoveAbsolute(0, speed, 0);
	}

	// Get mouse movement
	POINT mousePos = {};
	GetCursorPos(&mousePos);
	ScreenToClient(windowHandle, &mousePos);

	// Rotate if left mouse button is held down
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) 
	{
		float mouseSpeed = 3.0f;

		float xDiff = dt * mouseSpeed * (mousePos.x - prevMousePos.x);
		float yDiff = dt * mouseSpeed * (mousePos.y - prevMousePos.y);
		
		transform.Rotate(yDiff, xDiff, 0);
	}

	UpdateViewMatrix();

	// Set current mouse position to previous mouse position
	prevMousePos = mousePos;
}

DirectX::XMFLOAT4X4 Camera::GetViewMatrix()
{
	return view;
}

DirectX::XMFLOAT4X4 Camera::GetProjectionMatrix()
{
	return projection;
}

Transform Camera::GetTransform()
{
	return transform;
}