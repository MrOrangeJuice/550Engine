#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Transform
{
private:
	DirectX::XMFLOAT4X4 world;
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 scale;
	float pitch;
	float yaw;
	float roll;
public:
	Transform();

	void SetPosition(float x, float y, float z);
	void SetRotation(float pitch, float yaw, float roll);
	void SetScale(float x, float y, float z);

	DirectX::XMFLOAT3 GetPosition();
	DirectX::XMFLOAT3 GetPitchYawRoll();
	DirectX::XMFLOAT3 GetScale();
	DirectX::XMFLOAT4X4 GetWorldMatrix();

	void MoveAbsolute(float x, float y, float z);
	void MoveRelative(float x, float y, float z);
	void Rotate(float pitch, float yaw, float roll);
	void Scale(float x, float y, float z);
};

