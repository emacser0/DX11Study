#pragma once

struct FVertexData
{
	Vec3 Position = { 0, 0, 0 };
};

struct FVertexTextureData
{
	Vec3 Position = { 0, 0, 0 };
	Vec2 TexCoord = { 0, 0 };
};

struct FVertexColorData
{
	Vec3 Position = { 0, 0, 0 };
	Color Color = { 0, 0, 0, 0 };
};

struct FVertexTextureNormalData
{
	Vec3 Position = { 0, 0, 0 };
	Vec2 TexCoord = { 0, 0 };
	Vec3 normal = { 0, 0, 0 };
};