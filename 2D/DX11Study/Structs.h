#pragma once

struct FVertex
{
	FVector3 Position;
	//Color Color;
	FVector2 TexCoord;
};

using namespace DirectX;

struct FTransformData
{
	SimpleMath::Matrix World = SimpleMath::Matrix::Identity;
	SimpleMath::Matrix View = SimpleMath::Matrix::Identity;
	SimpleMath::Matrix Projection = SimpleMath::Matrix::Identity;
};
