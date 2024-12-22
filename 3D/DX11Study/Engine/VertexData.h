#pragma once

struct FVertexData
{
	FVector3 Position = { 0, 0, 0 };
};

struct FVertexTextureData
{
	FVector3 Position = { 0, 0, 0 };
	FVector2 TexCoord = { 0, 0 };
};

struct FVertexColorData
{
	FVector3 Position = { 0, 0, 0 };
	FColor Color = { 0, 0, 0, 0 };
};

struct FVertexTextureNormalData
{
	FVector3 Position = { 0, 0, 0 };
	FVector2 TexCoord = { 0, 0 };
	FVector3 Normal = { 0, 0, 0 };
};