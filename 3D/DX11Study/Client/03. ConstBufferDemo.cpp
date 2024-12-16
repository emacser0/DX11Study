#include "pch.h"
#include "03. ConstBufferDemo.h"

#include "GeometryHelper.h"

void FConstBufferDemo::Init()
{
	Shader = std::make_shared<FShader>(L"03. ConstBuffer.fx");

	Geometry = std::make_shared<FGeometry<FVertexColorData>>();
	FGeometryHelper::CreateQuad(Geometry, FColor(0.0f, 1.0f, 1.0f, 1.0f));

	VertexBuffer = std::make_shared<FVertexBuffer>();
	VertexBuffer->Create(Geometry->GetVertices());

	IndexBuffer = std::make_shared<FIndexBuffer>();
	IndexBuffer->Create(Geometry->GetIndices());
}

void FConstBufferDemo::Update()
{
	float DeltaTime = TIME->GetDeltaTime();

	if (INPUT->GetButton(EKeyType::A))
	{
		Translation.x -= 3.0f * DeltaTime;
	}
	else if (INPUT->GetButton(EKeyType::D))
	{
		Translation.x += 3.0f * DeltaTime;
	}
	else if (INPUT->GetButton(EKeyType::W))
	{
		Translation.y += 3.0f * DeltaTime;
	}
	else if (INPUT->GetButton(EKeyType::S))
	{
		Translation.y -= 3.0f * DeltaTime;
	}

	World = FMatrix::CreateTranslation(Translation);
}

void FConstBufferDemo::Render()
{
	Shader->GetMatrix("World")->SetMatrix((float*)&World);
	Shader->GetMatrix("View")->SetMatrix((float*)&View);
	Shader->GetMatrix("Projection")->SetMatrix((float*)&Projection);

	uint32 stride = VertexBuffer->GetStride();
	uint32 offset = VertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, VertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(IndexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	Shader->DrawIndexed(0, 0, IndexBuffer->GetCount(), 0, 0);
}
