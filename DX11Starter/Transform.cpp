#include "Transform.h"

// Initialize fields
Transform::Transform()
{
	position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
	pitch = 0.0f;
	yaw = 0.0f;
	roll = 0.0f;
	XMStoreFloat4x4(&world, DirectX::XMMatrixIdentity());
}

void Transform::SetPosition(float x, float y, float z)
{
	position = DirectX::XMFLOAT3(x, y, z);
}

void Transform::SetRotation(float pitch, float yaw, float roll)
{
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;
}

void Transform::SetScale(float x, float y, float z)
{
	scale = DirectX::XMFLOAT3(x, y, z);
}

DirectX::XMFLOAT3 Transform::GetPosition()
{
	return position;
}

DirectX::XMFLOAT3 Transform::GetPitchYawRoll()
{
	return DirectX::XMFLOAT3(pitch, yaw, roll);
}

DirectX::XMFLOAT3 Transform::GetScale()
{
	return scale;
}

DirectX::XMFLOAT4X4 Transform::GetWorldMatrix()
{
	// Calculate world matrix
	DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	DirectX::XMMATRIX scaleMat = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	DirectX::XMMATRIX worldMatrix = scaleMat * rotation * translation;
	DirectX::XMStoreFloat4x4(&world, worldMatrix);
	return world;
}

void Transform::MoveAbsolute(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
}

void Transform::MoveRelative(float x, float y, float z)
{
	DirectX::XMVECTOR relativeVector = DirectX::XMVectorSet(x,y,z,0);
	DirectX::XMVECTOR relativeQuat = DirectX::XMQuaternionRotationRollPitchYaw(GetPitchYawRoll().x, GetPitchYawRoll().y, GetPitchYawRoll().z);
	DirectX::XMVECTOR relativeTotal = DirectX::XMVector3Rotate(relativeVector, relativeQuat);
	DirectX::XMFLOAT3 currentPosition = position;
	DirectX::XMStoreFloat3(&position, DirectX::XMLoadFloat3(&position) + relativeTotal);
}

void Transform::Rotate(float pitch, float yaw, float roll)
{
	this->pitch += pitch;
	this->yaw += yaw;
	this->roll += roll;
}
void Transform::Scale(float x, float y, float z)
{
	scale.x *= x;
	scale.y *= y;
	scale.z *= z;
}