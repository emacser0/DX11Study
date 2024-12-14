#include "pch.h"
#include "Game.h"
#include "Graphics.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "GeometryHelper.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "Texture.h"
#include "RasterizerState.h"
#include "SamplerState.h"
#include "BlendState.h"

using namespace SimpleMath;

FGame::FGame()
	: Graphics(nullptr)
	, RasterizerState(nullptr)
	, SamplerState(nullptr)
	, BlendState(nullptr)
	, Geometry(nullptr)
	, VertexBuffer(nullptr)
	, IndexBuffer(nullptr)
	, InputLayout(nullptr)
	, VertexShader(nullptr)
	, PixelShader(nullptr)
	, Texture0(nullptr)
	, Texture1(nullptr)
	, LocalPosition({ 0.0f, 0.0f, 0.0f })
	, LocalRotation({ 0.0f, 0.0f, 0.0f })
	, LocalScale({ 1.0f, 1.0f, 1.0f })
{
}

FGame::~FGame()
{

}

void FGame::Init(HWND InWindowHandle)
{
	Graphics = std::make_shared<FGraphics>(InWindowHandle);

	ComPtr<ID3D11Device> Device = Graphics->GetDevice();
	ComPtr<ID3D11DeviceContext> DeviceContext = Graphics->GetDeviceContext();

	RasterizerState = std::make_shared<FRasterizerState>(Device);
	SamplerState = std::make_shared<FSamplerState>(Device);
	BlendState = std::make_shared<FBlendState>(Device);

	VertexBuffer = std::make_shared<FVertexBuffer>(Device);
	IndexBuffer = std::make_shared<FIndexBuffer>(Device);
	InputLayout = std::make_shared<FInputLayout>(Device);
	Geometry = std::make_shared<FGeometry<FVertexTextureData>>();
	VertexShader = std::make_shared<FVertexShader>(Device);
	PixelShader = std::make_shared<FPixelShader>(Device);
	ConstantBuffer = std::make_shared<FConstantBuffer<FTransformData>>(Device, DeviceContext);
	Texture0 = std::make_shared<FTexture>(Device);
	Texture1 = std::make_shared<FTexture>(Device);

	CreateRasterizerState();
	CreateSamplerState();
	CreateBlendState();

	CreateGeometry();
	CreateVS();
	CreatePS();
	CreateInputLayout();
	CreateSRV();
	CreateConstantBuffer();
}

void FGame::Update()
{
	Matrix Scale = Matrix::CreateScale(LocalScale);
	Matrix Rotation = Matrix::CreateRotationX(LocalRotation.x);
	Rotation *= Matrix::CreateRotationY(LocalRotation.y);
	Rotation *= Matrix::CreateRotationZ(LocalRotation.z);
	Matrix Translation = Matrix::CreateTranslation(LocalPosition);

	Matrix World = Scale * Rotation * Translation;
	TransformData.World = World;

	ConstantBuffer->CopyData(TransformData);
}

void FGame::Render()
{
	Graphics->RenderBegin();

	uint32 Stride = VertexBuffer->GetStride();
	uint32 Offset = VertexBuffer->GetOffset();

	ComPtr<ID3D11DeviceContext> DeviceContext = Graphics->GetDeviceContext();

	// IA
	DeviceContext->IASetVertexBuffers(0, 1, VertexBuffer->GetComPtr().GetAddressOf(), &Stride, &Offset);
	DeviceContext->IASetIndexBuffer(IndexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
	DeviceContext->IASetInputLayout(InputLayout->GetComPtr().Get());
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// VS
	DeviceContext->VSSetShader(VertexShader->GetComPtr().Get(), nullptr, 0);
	DeviceContext->VSSetConstantBuffers(0, 1, ConstantBuffer->GetComPtr().GetAddressOf());

	// RS
	DeviceContext->RSSetState(RasterizerState->GetComPtr().Get());

	// PS
	DeviceContext->PSSetShader(PixelShader->GetComPtr().Get(), nullptr, 0);
	DeviceContext->PSSetShaderResources(0, 1, Texture0->GetComPtr().GetAddressOf());
	DeviceContext->PSSetShaderResources(1, 1, Texture1->GetComPtr().GetAddressOf());
	DeviceContext->PSSetSamplers(0, 1, SamplerState->GetComPtr().GetAddressOf());

	// OM
	DeviceContext->OMSetBlendState(BlendState->GetComPtr().Get(), nullptr, 0xFFFFFFFF);

	DeviceContext->DrawIndexed(Geometry->GetIndices().size(), 0, 0);

	Graphics->RenderEnd();
}

void FGame::CreateRasterizerState()
{
	RasterizerState->Create();
}

void FGame::CreateSamplerState()
{
	SamplerState->Create();
}

void FGame::CreateBlendState()
{
	BlendState->Create();
}

void FGame::CreateGeometry()
{
	FGeometryHelper::CreateRectangle(Geometry);
	VertexBuffer->Create(Geometry->GetVertices());
	IndexBuffer->Create(Geometry->GetIndices());
}

void FGame::CreateInputLayout()
{
	InputLayout->Create(FVertexTextureData::Descs, VertexShader->GetBlob());
}

void FGame::CreateVS()
{
	VertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");
}

void FGame::CreatePS()
{
	PixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");
}

void FGame::CreateSRV()
{
	Texture0->Create(L"Skeleton.png");
	Texture1->Create(L"Golem.png");
}

void FGame::CreateConstantBuffer()
{
	ConstantBuffer->Create();
}
