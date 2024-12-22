#include "pch.h"
#include "Mesh.h"
#include "GeometryHelper.h"

FMesh::FMesh()
	: FResourceBase(EResourceType::Mesh)
{
}

FMesh::~FMesh()
{
}

void FMesh::CreateQuad()
{
	Geometry = std::make_shared<FGeometry<FVertexTextureNormalData>>();
	FGeometryHelper::CreateQuad(Geometry);
	CreateBuffers();
}

void FMesh::CreateCube()
{
}

void FMesh::CreateGrid(int32 InSizeX, int32 InSizeY)
{
}

void FMesh::CreateSphere()
{
}

void FMesh::CreateBuffers()
{
	VertexBuffer = std::make_shared<FVertexBuffer>();
	VertexBuffer->Create(Geometry->GetVertices());

	IndexBuffer = std::make_shared<FIndexBuffer>();
	IndexBuffer->Create(Geometry->GetIndices());
}
