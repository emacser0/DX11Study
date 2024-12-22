#pragma once

#include "Geometry.h"

class FGeometryHelper
{
public:
	static void CreateQuad(std::shared_ptr<FGeometry<FVertexColorData>> InGeometry, FColor InColor);

	static void CreateQuad(std::shared_ptr<FGeometry<FVertexTextureData>> InGeometry);
	static void CreateCube(std::shared_ptr<FGeometry<FVertexTextureData>> InGeometry);
	static void CreateGrid(std::shared_ptr<FGeometry<FVertexTextureData>> InGeometry, int32 InSizeX, int32 InSizeZ);
	static void CreateSphere(std::shared_ptr<FGeometry<FVertexTextureData>> InGeometry);

	static void CreateQuad(std::shared_ptr<FGeometry<FVertexTextureNormalData>> InGeometry);
	static void CreateCube(std::shared_ptr<FGeometry<FVertexTextureNormalData>> InGeometry);
	static void CreateGrid(std::shared_ptr<FGeometry<FVertexTextureNormalData>> InGeometry, int32 InSizeX, int32 InSizeZ);
	static void CreateSphere(std::shared_ptr<FGeometry<FVertexTextureNormalData>> InGeometry);
};
