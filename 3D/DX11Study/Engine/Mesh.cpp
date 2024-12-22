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
	Geometry = std::make_shared<FGeometry<FVertexTextureNormalData>>();
	FGeometryHelper::CreateCube(Geometry);
	CreateBuffers();
}

void FMesh::CreateGrid(int32 InSizeX, int32 InSizeY)
{
	Geometry = std::make_shared<FGeometry<FVertexTextureNormalData>>();
	FGeometryHelper::CreateGrid(Geometry, InSizeX, InSizeY);
	CreateBuffers();
}

void FMesh::CreateSphere()
{
	Geometry = std::make_shared<FGeometry<FVertexTextureNormalData>>();
	FGeometryHelper::CreateSphere(Geometry);
	CreateBuffers();
}

void FMesh::CreateBuffers()
{
	VertexBuffer = std::make_shared<FVertexBuffer>();
	VertexBuffer->Create(Geometry->GetVertices());

	IndexBuffer = std::make_shared<FIndexBuffer>();
	IndexBuffer->Create(Geometry->GetIndices());
}
