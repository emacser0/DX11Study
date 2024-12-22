#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Game.h"
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Texture.h"

FMeshRenderer::FMeshRenderer()
	: Super(EComponentType::MeshRenderer)
{
}

FMeshRenderer::~FMeshRenderer()
{

}

void FMeshRenderer::Update()
{
	if (Mesh == nullptr || Texture == nullptr || Shader == nullptr)
	{
		return;
	}

	FMatrix World = GetTransform()->GetWorldMatrix();
	Shader->GetMatrix("World")->SetMatrix((float*)&World);
	Shader->GetMatrix("View")->SetMatrix((float*)&FCamera::S_View);
	Shader->GetMatrix("Projection")->SetMatrix((float*)&FCamera::S_Projection);

	Shader->GetSRV("Texture0")->SetResource(Texture->GetComPtr().Get());

	FVector3 LightDirection(0.0f, 0.0f, 1.0f);
	Shader->GetVector("LightDir")->SetFloatVector((float*)&LightDirection);

	uint32 Stride = Mesh->GetVertexBuffer()->GetStride();
	uint32 Offset = Mesh->GetVertexBuffer()->GetOffset();

	DC->IASetVertexBuffers(0, 1, Mesh->GetVertexBuffer()->GetComPtr().GetAddressOf(), &Stride, &Offset);
	DC->IASetIndexBuffer(Mesh->GetIndexBuffer()->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	Shader->DrawIndexed(0, 0, Mesh->GetIndexBuffer()->GetCount(), 0, 0);
}
