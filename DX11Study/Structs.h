#pragma once

struct FVertex
{
	Vec3 Position;
	//Color Color;
	Vec2 TexCoord;
};

struct alignas(16) FTransformData
{
	Vec3 Offset;
};
