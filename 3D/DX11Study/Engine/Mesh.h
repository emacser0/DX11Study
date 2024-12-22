#pragma once

#include "ResourceBase.h"
#include "Geometry.h"

class FMesh : public FResourceBase
{
public:
	FMesh();
	virtual ~FMesh();

	void CreateQuad();
	void CreateCube();
	void CreateGrid(int32 InSizeX, int32 InSizeY);
	void CreateSphere();

	std::shared_ptr<FVertexBuffer> GetVertexBuffer() const { return VertexBuffer; }
	std::shared_ptr<FIndexBuffer> GetIndexBuffer() const { return IndexBuffer; }

private:
	void CreateBuffers();

private:
	std::shared_ptr<FGeometry<FVertexTextureNormalData>> Geometry;
	std::shared_ptr<FVertexBuffer> VertexBuffer;
	std::shared_ptr<FIndexBuffer> IndexBuffer;
};
