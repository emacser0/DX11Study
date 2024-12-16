#include "pch.h"
#include "02. QuadDemo.h"

#include "GeometryHelper.h"

void FQuadDemo::Init()
{
	Shader = std::make_shared<FShader>(L"02. Quad.fx");

	Geometry = std::make_shared<FGeometry<FVertexColorData>>();
	FGeometryHelper::CreateQuad(Geometry, FColor(0.0f, 1.0f, 1.0f, 1.0f));

	VertexBuffer = std::make_shared<FVertexBuffer>();
	VertexBuffer->Create(Geometry->GetVertices());

	IndexBuffer = std::make_shared<FIndexBuffer>();
	IndexBuffer->Create(Geometry->GetIndices());
}

void FQuadDemo::Update()
{
}

void FQuadDemo::Render()
{
	uint32 stride = VertexBuffer->GetStride();
	uint32 offset = VertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, VertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(IndexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	Shader->DrawIndexed(0, 0, IndexBuffer->GetCount(), 0, 0);
}
