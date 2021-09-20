#pragma once
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"

class Entity
{
private:
	Transform transform;
	Mesh* mesh;
	Material* material;
public:
	Entity(Mesh* meshPtr, Material* matPtr);

	Mesh* GetMesh();
	Transform* GetTransform();
	Material* GetMaterial();
};

