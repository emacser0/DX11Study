#pragma once

struct FVertex
{
	Vec3 Position;
	//Color Color;
	Vec2 TexCoord;
};

using namespace DirectX;

struct FTransformData
{
	Math::Matrix World = Math::Matrix::Identity;
	Math::Matrix View = Math::Matrix::Identity;
	Math::Matrix Projection = Math::Matrix::Identity;
};
