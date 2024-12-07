#include "pch.h"
#include "Game.h"

FGame::FGame()
	: WindowHandle(NULL)
	, Width(0)
	, Height(0)
	, Device(nullptr)
	, DeviceContext(nullptr)
	, SwapChain(nullptr)
	, RenderTargetView(nullptr)
	, Viewport({})
	, ClearColor{ 0.0f, 0.0f, 0.0f, 1.0f }
	, RasterizerState(nullptr)
	, VertexBuffer(nullptr)
	, InputLayout(nullptr)
	, VertexShader(nullptr)
	, VSBlob(nullptr)
	, PixelShader(nullptr)
	, PSBlob(nullptr)
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
	WindowHandle = InWindowHandle;
	Width = GWindowSizeX;
	Height = GWindowSizeY;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewport();

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
	SimpleMath::Matrix Scale = SimpleMath::Matrix::CreateScale(LocalScale);
	SimpleMath::Matrix Rotation = SimpleMath::Matrix::CreateRotationX(LocalRotation.x);
	Rotation *= SimpleMath::Matrix::CreateRotationY(LocalRotation.y);
	Rotation *= SimpleMath::Matrix::CreateRotationZ(LocalRotation.z);
	SimpleMath::Matrix Translation = SimpleMath::Matrix::CreateTranslation(LocalPosition);

	SimpleMath::Matrix World = Scale * Rotation * Translation;
	TransformData.World = World;

	D3D11_MAPPED_SUBRESOURCE SubResource;
	ZeroMemory(&SubResource, sizeof(SubResource));

	DeviceContext->Map(ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &SubResource);
	memcpy(SubResource.pData, &TransformData, sizeof(TransformData));
	DeviceContext->Unmap(ConstantBuffer.Get(), 0);
}

void FGame::Render()
{
	RenderBegin();

	uint32 Stride = sizeof(FVertex);
	uint32 Offset = 0;

	// IA
	DeviceContext->IASetVertexBuffers(0, 1, VertexBuffer.GetAddressOf(), &Stride, &Offset);
	DeviceContext->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	DeviceContext->IASetInputLayout(InputLayout.Get());
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

	DeviceContext->DrawIndexed(Indices.size(), 0, 0);

	RenderEnd();
}

void FGame::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC SwapchainDesc{};
	ZeroMemory(&SwapchainDesc, sizeof(SwapchainDesc));

	SwapchainDesc.BufferDesc.Width = Width;
	SwapchainDesc.BufferDesc.Height = Height;
	SwapchainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapchainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapchainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapchainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapchainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapchainDesc.SampleDesc.Count = 1;
	SwapchainDesc.SampleDesc.Quality = 0;
	SwapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapchainDesc.BufferCount = 1;
	SwapchainDesc.OutputWindow = WindowHandle;
	SwapchainDesc.Windowed = true;
	SwapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	HRESULT hr = ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&SwapchainDesc,
		SwapChain.GetAddressOf(),
		Device.GetAddressOf(),
		nullptr,
		DeviceContext.GetAddressOf());

	CHECK(hr);
}

void FGame::CreateRenderTargetView()
{
	HRESULT hr;

	ComPtr<ID3D11Texture2D> BackBuffer = nullptr;
	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)BackBuffer.GetAddressOf());
	CHECK(hr);

	hr = Device->CreateRenderTargetView(BackBuffer.Get(), nullptr, RenderTargetView.GetAddressOf());
	CHECK(hr);
}

void FGame::SetViewport()
{
	Viewport.TopLeftX = 0;
	Viewport.TopLeftY = 0;
	Viewport.Width = static_cast<float>(Width);
	Viewport.Height = static_cast<float>(Height);
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 0.0f;
}

void FGame::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC RasterizerDesc{};
	ZeroMemory(&RasterizerDesc, sizeof(RasterizerDesc));
	RasterizerDesc.FillMode = D3D11_FILL_SOLID;
	RasterizerDesc.CullMode = D3D11_CULL_NONE;
	RasterizerDesc.FrontCounterClockwise = false;

	HRESULT hr = Device->CreateRasterizerState(&RasterizerDesc, RasterizerState.GetAddressOf());
	CHECK(hr);
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

	HRESULT hr = Device->CreateSamplerState(&SamplerDesc, SamplerState.GetAddressOf());
	CHECK(hr);
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

	HRESULT hr = Device->CreateBlendState(&BlendDesc, BlendState.GetAddressOf());
	CHECK(hr);
}

void FGame::CreateGeometry()
{
	{
		Vertices.resize(4);
		Vertices[0].Position = Vec3(-0.5f, -0.5f, 0.0f);
//		Vertices[0].Color = Color(1.0f, 0.0f, 0.0f, 1.0f);
		Vertices[0].TexCoord = Vec2(0.0f, 1.0f);
		
		Vertices[1].Position = Vec3(-0.5f, 0.5f, 0.0f);
//		Vertices[1].Color = Color(1.0f, 0.0f, 0.0f, 1.0f);
		Vertices[1].TexCoord = Vec2(0.0f, 0.0f);

		Vertices[2].Position = Vec3(0.5f, -0.5f, 0.0f);
//		Vertices[2].Color = Color(1.0f, 0.0f, 0.0f, 1.0f);
		Vertices[2].TexCoord = Vec2(1.0f, 1.0f);

		Vertices[3].Position = Vec3(0.5f, 0.5f, 0.0f);
//		Vertices[3].Color = Color(1.0f, 0.0f, 0.0f, 1.0f);
		Vertices[3].TexCoord = Vec2(1.0f, 0.0f);
	}

	{
		D3D11_BUFFER_DESC BufferDesc{};
		ZeroMemory(&BufferDesc, sizeof(BufferDesc));
		BufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		BufferDesc.ByteWidth = static_cast<uint32>(sizeof(FVertex) * Vertices.size());

		D3D11_SUBRESOURCE_DATA Data;
		ZeroMemory(&Data, sizeof(Data));
		Data.pSysMem = Vertices.data();

		HRESULT hr = Device->CreateBuffer(&BufferDesc, &Data, VertexBuffer.GetAddressOf());
		CHECK(hr);
	}

	{
		Indices = { 0, 1, 2, 2, 1, 3 };
	}

	{
		D3D11_BUFFER_DESC BufferDesc{};
		ZeroMemory(&BufferDesc, sizeof(BufferDesc));
		BufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		BufferDesc.ByteWidth = static_cast<uint32>(sizeof(uint32) * Indices.size());

		D3D11_SUBRESOURCE_DATA Data;
		ZeroMemory(&Data, sizeof(Data));
		Data.pSysMem = Indices.data();

		HRESULT hr = Device->CreateBuffer(&BufferDesc, &Data, IndexBuffer.GetAddressOf());
		CHECK(hr);
	}
}

void FGame::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA },
//		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA }
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA }
	};

	const int32 Count = sizeof(LayoutDesc) / sizeof(D3D11_INPUT_ELEMENT_DESC);
	Device->CreateInputLayout(LayoutDesc, Count, VSBlob->GetBufferPointer(), VSBlob->GetBufferSize(), InputLayout.GetAddressOf());
}

void FGame::CreateVS()
{
	LoadShaderFromFile(L"Default.hlsl", "VS", "vs_5_0", VSBlob);

	HRESULT hr = Device->CreateVertexShader(VSBlob->GetBufferPointer(), VSBlob->GetBufferSize(), nullptr, VertexShader.GetAddressOf());
	CHECK(hr);
}

void FGame::CreatePS()
{
	LoadShaderFromFile(L"Default.hlsl", "PS", "ps_5_0", PSBlob);
	HRESULT hr = Device->CreatePixelShader(PSBlob->GetBufferPointer(), PSBlob->GetBufferSize(), nullptr, PixelShader.GetAddressOf());
	CHECK(hr);
}

void FGame::CreateSRV()
{
	TexMetadata Metadata;
	ScratchImage Image;
	HRESULT hr = ::LoadFromWICFile(L"Skeleton.png", WIC_FLAGS_NONE, &Metadata, Image);
	CHECK(hr);

	hr = ::CreateShaderResourceView(Device.Get(), Image.GetImages(), Image.GetImageCount(), Metadata, ShaderResourceView0.GetAddressOf());
	CHECK(hr);

	hr = ::LoadFromWICFile(L"Golem.png", WIC_FLAGS_NONE, &Metadata, Image);
	CHECK(hr);

	hr = ::CreateShaderResourceView(Device.Get(), Image.GetImages(), Image.GetImageCount(), Metadata, ShaderResourceView1.GetAddressOf());
	CHECK(hr);
}

void FGame::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.ByteWidth = sizeof(FTransformData);
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = Device->CreateBuffer(&BufferDesc, nullptr, ConstantBuffer.GetAddressOf());
}

void FGame::LoadShaderFromFile(const std::wstring& InPath, const std::string& InName, const std::string& InVersion, ComPtr<ID3DBlob>& OutBlob)
{
#if __DEBUG
	const int32 CompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	const int32 CompileFlags = D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	HRESULT hr = ::D3DCompileFromFile(
		InPath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		InName.c_str(),
		InVersion.c_str(),
		CompileFlags,
		0,
		OutBlob.GetAddressOf(),
		nullptr);
	CHECK(hr);
}

void FGame::RenderBegin()
{
	DeviceContext->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), nullptr);
	DeviceContext->ClearRenderTargetView(RenderTargetView.Get(), ClearColor);
	DeviceContext->RSSetViewports(1, &Viewport);
}

void FGame::RenderEnd()
{
	HRESULT hr = SwapChain->Present(1, 0);
	CHECK(hr);
}
