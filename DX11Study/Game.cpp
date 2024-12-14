#include "pch.h"
#include "Game.h"
#include "Graphics.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "GeometryHelper.h"
#include "Shader.h"

using namespace SimpleMath;

FGame::FGame()
	: Graphics(nullptr)
	, RasterizerState(nullptr)
	, Geometry(nullptr)
	, VertexBuffer(nullptr)
	, IndexBuffer(nullptr)
	, InputLayout(nullptr)
	, VertexShader(nullptr)
	, PixelShader(nullptr)
	, ShaderResourceView0(nullptr)
	, ShaderResourceView1(nullptr)
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
	VertexBuffer = std::make_shared<FVertexBuffer>(Graphics->GetDevice());
	IndexBuffer = std::make_shared<FIndexBuffer>(Graphics->GetDevice());
	InputLayout = std::make_shared<FInputLayout>(Graphics->GetDevice());
	Geometry = std::make_shared<FGeometry<FVertexTextureData>>();

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

	D3D11_MAPPED_SUBRESOURCE SubResource;
	ZeroMemory(&SubResource, sizeof(SubResource));

	ComPtr<ID3D11DeviceContext> DeviceContext = Graphics->GetDeviceContext();

	DeviceContext->Map(ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &SubResource);
	memcpy(SubResource.pData, &TransformData, sizeof(TransformData));
	DeviceContext->Unmap(ConstantBuffer.Get(), 0);
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
	DeviceContext->VSSetShader(VertexShader.Get(), nullptr, 0);
	DeviceContext->VSSetConstantBuffers(0, 1, ConstantBuffer.GetAddressOf());

	// RS
	DeviceContext->RSSetState(RasterizerState.Get());

	// PS
	DeviceContext->PSSetShader(PixelShader.Get(), nullptr, 0);
	DeviceContext->PSSetShaderResources(0, 1, ShaderResourceView0.GetAddressOf());
	DeviceContext->PSSetShaderResources(1, 1, ShaderResourceView1.GetAddressOf());
	DeviceContext->PSSetSamplers(0, 1, SamplerState.GetAddressOf());

	// OM
	DeviceContext->OMSetBlendState(BlendState.Get(), nullptr, 0xFFFFFFFF);

	DeviceContext->DrawIndexed(Geometry->GetIndices().size(), 0, 0);

	Graphics->RenderEnd();
}

void FGame::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC RasterizerDesc{};
	ZeroMemory(&RasterizerDesc, sizeof(RasterizerDesc));
	RasterizerDesc.FillMode = D3D11_FILL_SOLID;
	RasterizerDesc.CullMode = D3D11_CULL_NONE;
	RasterizerDesc.FrontCounterClockwise = false;

	HRESULT Result = Graphics->GetDevice()->CreateRasterizerState(&RasterizerDesc, RasterizerState.GetAddressOf());
	CHECK(Result);
}

void FGame::CreateSamplerState()
{
	D3D11_SAMPLER_DESC SamplerDesc{};
	ZeroMemory(&SamplerDesc, sizeof(SamplerDesc));

	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	SamplerDesc.BorderColor[0] = 1.0f;
	SamplerDesc.BorderColor[1] = 0.0f;
	SamplerDesc.BorderColor[2] = 0.0f;
	SamplerDesc.BorderColor[3] = 1.0f;
	SamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	SamplerDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	SamplerDesc.MaxAnisotropy = 16;
	SamplerDesc.MaxLOD = FLT_MAX;
	SamplerDesc.MinLOD = FLT_MIN;
	SamplerDesc.MipLODBias = 0;

	HRESULT Result = Graphics->GetDevice()->CreateSamplerState(&SamplerDesc, SamplerState.GetAddressOf());
	CHECK(Result);
}

void FGame::CreateBlendState()
{
	D3D11_BLEND_DESC BlendDesc{};
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));

	BlendDesc.RenderTarget[0].BlendEnable = true;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HRESULT Result = Graphics->GetDevice()->CreateBlendState(&BlendDesc, BlendState.GetAddressOf());
	CHECK(Result);
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
	TexMetadata Metadata;
	ScratchImage Image;
	HRESULT Result = ::LoadFromWICFile(L"Skeleton.png", WIC_FLAGS_NONE, &Metadata, Image);
	CHECK(Result);

	ComPtr<ID3D11Device> Device = Graphics->GetDevice();

	Result = ::CreateShaderResourceView(Device.Get(), Image.GetImages(), Image.GetImageCount(), Metadata, ShaderResourceView0.GetAddressOf());
	CHECK(Result);

	Result = ::LoadFromWICFile(L"Golem.png", WIC_FLAGS_NONE, &Metadata, Image);
	CHECK(Result);

	Result = ::CreateShaderResourceView(Device.Get(), Image.GetImages(), Image.GetImageCount(), Metadata, ShaderResourceView1.GetAddressOf());
	CHECK(Result);
}

void FGame::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.ByteWidth = sizeof(FTransformData);
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	ComPtr<ID3D11Device> Device = Graphics->GetDevice();

	HRESULT Result = Device->CreateBuffer(&BufferDesc, nullptr, ConstantBuffer.GetAddressOf());
}
