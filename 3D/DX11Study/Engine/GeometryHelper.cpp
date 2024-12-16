#include "pch.h"
#include "GeometryHelper.h"

void FGeometryHelper::CreateQuad(std::shared_ptr<FGeometry<FVertexColorData>> InGeometry, FColor InColor)
{
	std::vector<FVertexColorData> Vertices;
	Vertices.resize(4);
	Vertices[0].Position = FVector3(-0.5f, 0.5f, 0.0f);
	Vertices[0].Color = InColor;
	Vertices[1].Position = FVector3(0.5f, 0.5f, 0.0f);
	Vertices[1].Color = InColor;
	Vertices[2].Position = FVector3(-0.5f, -0.5f, 0.0f);
	Vertices[2].Color = InColor;
	Vertices[3].Position = FVector3(0.5f, -0.5f, 0.0f);
	Vertices[3].Color = InColor;

	std::vector<uint32> Indices = { 0, 1, 2, 2, 1, 3 };

	InGeometry->SetVertices(Vertices);
	InGeometry->SetIndices(Indices);
}
