#include "pch.h"
#include "GameObject.h"

#include "Transform.h"

#include "Shader.h"
#include "InputLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Geometry.h"
#include "GeometryHelper.h"
#include "RasterizerState.h"
#include "SamplerState.h"
#include "BlendState.h"
#include "Texture.h"
#include "Pipeline.h"

UGameObject::UGameObject(ComPtr<ID3D11Device> InDevice, ComPtr<ID3D11DeviceContext> InDeviceContext)
	: Device(InDevice)
	, DeviceContext(InDeviceContext)
	, RasterizerState(nullptr)
	, SamplerState(nullptr)
	, BlendState(nullptr)
	, VertexBuffer(nullptr)
	, IndexBuffer(nullptr)
	, InputLayout(nullptr)
	, VertexShader(nullptr)
	, PixelShader(nullptr)
	, Texture(nullptr)
	, Transform(std::make_shared<FTransform>())
	, Parent(std::make_shared<FTransform>())
{
	VertexShader = std::make_shared<FVertexShader>(Device);
	VertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

	PixelShader = std::make_shared<FPixelShader>(Device);
	PixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	InputLayout = std::make_shared<FInputLayout>(Device);
	InputLayout->Create(FVertexTextureData::Descs, VertexShader->GetBlob());

	Geometry = std::make_shared<FGeometry<FVertexTextureData>>();
	FGeometryHelper::CreateRectangle(Geometry);

	VertexBuffer = std::make_shared<FVertexBuffer>(Device);
	VertexBuffer->Create(Geometry->GetVertices());

	IndexBuffer = std::make_shared<FIndexBuffer>(Device);
	IndexBuffer->Create(Geometry->GetIndices());

	RasterizerState = std::make_shared<FRasterizerState>(Device);
	RasterizerState->Create();

	SamplerState = std::make_shared<FSamplerState>(Device);
	SamplerState->Create();

	BlendState = std::make_shared<FBlendState>(Device);
	BlendState->Create();

	ConstantBuffer = std::make_shared<FConstantBuffer<FTransformData>>(Device, DeviceContext);
	ConstantBuffer->Create();

	Texture = std::make_shared<FTexture>(Device);
	Texture->Create(L"Skeleton.png");

	Parent->AddChild(Transform);
	Transform->SetParent(Parent);
}

void UGameObject::Update()
{	
	FVector3 Position = Parent->GetPosition();
	Position.x += 0.001f;
	Parent->SetPosition(Position);

	FVector3 Rotation = Parent->GetRotation();
	Rotation.z += 0.01f;
	Parent->SetRotation(Rotation);

	TransformData.World = Transform->GetWorldMatrix();

	ConstantBuffer->CopyData(TransformData);
}

void UGameObject::Render(std::shared_ptr<FPipeline> InPipeline)
{
	FPipelineInfo PipelineInfo;
	PipelineInfo.InputLayout = InputLayout;
	PipelineInfo.VertexShader = VertexShader;
	PipelineInfo.PixelShader = PixelShader;
	PipelineInfo.RasterizerState = RasterizerState;
	PipelineInfo.BlendState = BlendState;
	InPipeline->UpdatePipeline(PipelineInfo);

	InPipeline->SetVertexBuffer(VertexBuffer);
	InPipeline->SetIndexBuffer(IndexBuffer);
	InPipeline->SetConstantBuffer(0, SS_VertexShader, ConstantBuffer);
	InPipeline->SetTexture(0, SS_PixelShader, Texture);
	InPipeline->SetSamplerState(0, SS_PixelShader, SamplerState);

	InPipeline->DrawIndexed(Geometry->GetIndices().size(), 0, 0);
}
