#pragma once

#include "Geometry.h"
#include "VertexData.h"

class FGeometryHelper
{
public:
	static void CreateRectangle(std::shared_ptr<FGeometry<FVertexColorData>> Geometry);
	static void CreateRectangle(std::shared_ptr<FGeometry<FVertexTextureData>> Geometry);
};

