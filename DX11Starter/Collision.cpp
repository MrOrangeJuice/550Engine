#include "Collision.h"

// Default constructor
Collision::Collision()
{
	this->x1 = 0.0f;
	this->x2 = 0.0f;
	this->y1 = 0.0f;
	this->y2 = 0.0f;
	this->z1 = 0.0f;
	this->z2 = 0.0f;
}

// Set collision box values
Collision::Collision(float x1, float x2, float y1, float y2, float z1, float z2)
{
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
	this->z1 = z1;
	this->z2 = z2;
}
