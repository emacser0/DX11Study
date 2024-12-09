#include "pch.h"
#include "GeometryHelper.h"

void FGeometryHelper::CreateRectangle(std::shared_ptr<FGeometry<FVertexColorData>> Geometry)
{
	static std::vector<FVertexColorData> Vertices;
	static std::vector<uint32> Indices = { 0, 1, 2, 2, 1 ,3 };
	static bool bInitialized = false;

	if (!bInitialized)
	{
		Vertices.resize(4);
		Vertices[0].Position = FVector3(-0.5f, -0.5f, 0.0f);
		Vertices[0].Color = FColor(1.0f, 0.0f, 0.0f, 1.0f);
		
		Vertices[1].Position = FVector3(-0.5f, 0.5f, 0.0f);
		Vertices[1].Color = FColor(1.0f, 0.0f, 0.0f, 1.0f);

		Vertices[2].Position = FVector3(0.5f, -0.5f, 0.0f);
		Vertices[2].Color = FColor(1.0f, 0.0f, 0.0f, 1.0f);

		Vertices[3].Position = FVector3(0.5f, 0.5f, 0.0f);
		Vertices[3].Color = FColor(1.0f, 0.0f, 0.0f, 1.0f);

		bInitialized = true;
	}

	Geometry->SetVertices(Vertices);
	Geometry->SetIndices(Indices);
}

void FGeometryHelper::CreateRectangle(std::shared_ptr<FGeometry<FVertexTextureData>> Geometry)
{
	static std::vector<FVertexTextureData> Vertices;
	static std::vector<uint32> Indices = { 0, 1, 2, 2, 1 ,3 };
	static bool bInitialized = false;

	if (!bInitialized)
	{
		Vertices.resize(4);
		Vertices[0].Position = FVector3(-0.5f, -0.5f, 0.0f);
		Vertices[0].TexCoord = FVector2(0.0f, 1.0f);
		
		Vertices[1].Position = FVector3(-0.5f, 0.5f, 0.0f);
		Vertices[1].TexCoord = FVector2(0.0f, 0.0f);

		Vertices[2].Position = FVector3(0.5f, -0.5f, 0.0f);
		Vertices[2].TexCoord = FVector2(1.0f, 1.0f);

		Vertices[3].Position = FVector3(0.5f, 0.5f, 0.0f);
		Vertices[3].TexCoord = FVector2(1.0f, 0.0f);

		bInitialized = true;
	}

	Geometry->SetVertices(Vertices);
	Geometry->SetIndices(Indices);
}

