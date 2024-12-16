#pragma once

#include "Geometry.h"

class FGeometryHelper
{
public:
	static void CreateQuad(std::shared_ptr<FGeometry<FVertexColorData>> InGeometry, FColor InColor);
};
