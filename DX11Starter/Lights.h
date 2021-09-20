#pragma once

#include <DirectXMath.h>

using namespace DirectX;

struct DirectionalLight {
	XMFLOAT3 color;
	float intensity;
	XMFLOAT3 direction;
};

struct PointLight {
	XMFLOAT3 color;
	float intensity;
	XMFLOAT3 position;
};