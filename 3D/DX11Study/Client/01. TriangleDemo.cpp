#include "pch.h"
#include "01. TriangleDemo.h"

void FTriangleDemo::Init()
{
	Shader = std::make_shared<FShader>(L"01. Triangle.fx");

	{
		Vertices.resize(3);
		Vertices[0].Position = FVector3(-0.5f, 0.0f, 0.0f);
		Vertices[1].Position = FVector3(0.0f, 0.5f, 0.0f);
		Vertices[2].Position = FVector3(0.5f, 0.0f, 0.0f);
	}

	Buffer = std::make_shared<FVertexBuffer>();
	Buffer->Create(Vertices);
}

void FTriangleDemo::Update()
{
}

void FTriangleDemo::Render()
{
	uint32 stride = Buffer->GetStride();
	uint32 offset = Buffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, Buffer->GetComPtr().GetAddressOf(), &stride, &offset);

	Shader->Draw(0, 0, 3);
}
