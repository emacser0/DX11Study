#include "pch.h"
#include "Graphics.h"

FGraphics::FGraphics(HWND InWindowHandle)
	: WindowHandle(InWindowHandle)
	, Width(GWindowSizeX)
	, Height(GWindowSizeY)
	, Device(nullptr)
	, DeviceContext(nullptr)
	, SwapChain(nullptr)
{
	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewport();
}

void FGraphics::CreateDeviceAndSwapChain()
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

	HRESULT Result = ::D3D11CreateDeviceAndSwapChain(
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
	Viewport.TopLeftX = 0;
	Viewport.TopLeftY = 0;
	Viewport.Width = static_cast<float>(Width);
	Viewport.Height = static_cast<float>(Height);
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 0.0f;
}

void FGraphics::RenderBegin()
{
	DeviceContext->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), nullptr);
	DeviceContext->ClearRenderTargetView(RenderTargetView.Get(), ClearColor);
	DeviceContext->RSSetViewports(1, &Viewport);
}

void FGraphics::RenderEnd()
{
	HRESULT Result = SwapChain->Present(1, 0);
	CHECK(Result);
}
