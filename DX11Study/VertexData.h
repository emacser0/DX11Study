#pragma once

struct FVertexColorData
{
	FVector3 Position = { 0.0f, 0.0f, 0.0f };
	FColor Color = { 0.0f, 0.0f, 0.0f, 0.0f };

	static std::vector<D3D11_INPUT_ELEMENT_DESC> Descs;
};

struct FVertexTextureData
{
	FVector3 Position = { 0.0f, 0.0f, 0.0f };
	FVector2 TexCoord = { 0.0f, 0.0f };

	static std::vector<D3D11_INPUT_ELEMENT_DESC> Descs;
};
