#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "Vertex.h"
#include <fstream>
#include <vector>

using namespace DirectX;
using namespace std;

class Mesh
{
	private:
		// Initalize buffer variables
		int indNum;
		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* indexBuffer;
	public:
		// Constructors and destructor
		Mesh(Vertex vertices[], int vertNum, unsigned int indices[], int indNum, ID3D11Device* bufferCreation);
		Mesh(const char* fileName, ID3D11Device* bufferCreation);
		~Mesh();

		// Methods
		void CalculateTangents(Vertex* verts, int numVerts, unsigned int* indices, int numIndices);
		ID3D11Buffer* GetVertexBuffer();
		ID3D11Buffer* GetIndexBuffer();
		int GetIndexCount();
};

