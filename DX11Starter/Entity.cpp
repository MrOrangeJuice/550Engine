#include "Entity.h"

Entity::Entity(Mesh* meshPtr, Material* matPtr)
{
	mesh = meshPtr;
	material = matPtr;
}

Mesh* Entity::GetMesh()
{
	return mesh;
}

Transform* Entity::GetTransform()
{
	return &transform;
}

Material* Entity::GetMaterial()
{
	return material;
}
