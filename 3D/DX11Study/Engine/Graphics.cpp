#include "pch.h"
#include "Graphics.h"

void FGraphics::Init(HWND InHwnd)
{
	hwnd = InHwnd;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewport();
}

void FGraphics::RenderBegin()
{
	DeviceContext->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), nullptr);
	DeviceContext->ClearRenderTargetView(RenderTargetView.Get(), (float*)(&GAME->GetGameDesc().ClearColor));
	DeviceContext->RSSetViewports(1, &Viewport);
}

void FGraphics::RenderEnd()
{
	HRESULT Result = SwapChain->Present(1, 0);
	CHECK(Result);
}
void FGraphics::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC Desc;
	ZeroMemory(&Desc, sizeof(Desc));
	{
		Desc.BufferDesc.Width = GAME->GetGameDesc().Width;
		Desc.BufferDesc.Height = GAME->GetGameDesc().Height;
		Desc.BufferDesc.RefreshRate.Numerator = 60;
		Desc.BufferDesc.RefreshRate.Denominator = 1;
		Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		Desc.SampleDesc.Count = 1;
		Desc.SampleDesc.Quality = 0;
		Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		Desc.BufferCount = 1;
		Desc.OutputWindow = hwnd;
		Desc.Windowed = TRUE;
		Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	HRESULT Result = ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&Desc,
		SwapChain.GetAddressOf(),
		Device.GetAddressOf(),
		nullptr,
		DeviceContext.GetAddressOf()
	);

	CHECK(Result);
}

void FGraphics::CreateRenderTargetView()
{
	HRESULT Result;

	ComPtr<ID3D11Texture2D> BackBuffer = nullptr;
	Result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)BackBuffer.GetAddressOf());
	CHECK(Result);

	Result = Device->CreateRenderTargetView(BackBuffer.Get(), nullptr, RenderTargetView.GetAddressOf());
	CHECK(Result);
}

void FGraphics::SetViewport()
{
	Viewport.TopLeftX = 0.0f;
	Viewport.TopLeftY = 0.0f;
	Viewport.Width = static_cast<float>(GAME->GetGameDesc().Width);
	Viewport.Height = static_cast<float>(GAME->GetGameDesc().Height);
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;
}