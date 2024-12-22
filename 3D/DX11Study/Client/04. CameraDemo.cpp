#include "pch.h"
#include "04. CameraDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "CameraScript.h"
#include "GameObject.h"

void FCameraDemo::Init()
{
	Shader = std::make_shared<FShader>(L"03. ConstBuffer.fx");

	Geometry = std::make_shared<FGeometry<FVertexColorData>>();
	FGeometryHelper::CreateQuad(Geometry, FColor(0.0f, 1.0f, 0.0f, 1.0f));

	VertexBuffer = std::make_shared<FVertexBuffer>();
	VertexBuffer->Create(Geometry->GetVertices());

	IndexBuffer = std::make_shared<FIndexBuffer>();
	IndexBuffer->Create(Geometry->GetIndices());

	Camera = std::make_shared<FGameObject>();
	Camera->GetOrAddTransform();
	Camera->AddComponent(std::make_shared<FCamera>());
	Camera->AddComponent(std::make_shared<FCameraScript>());

}

void FCameraDemo::Update()
{
	Camera->Update();
}

void FCameraDemo::Render()
{	
	Shader->GetMatrix("World")->SetMatrix((float*)&World);
	Shader->GetMatrix("View")->SetMatrix((float*)&FCamera::S_View);
	Shader->GetMatrix("Projection")->SetMatrix((float*)&FCamera::S_Projection);

	uint32 stride = VertexBuffer->GetStride();
	uint32 offset = VertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, VertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(IndexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	Shader->DrawIndexed(0, 0, IndexBuffer->GetCount(), 0, 0);
}
