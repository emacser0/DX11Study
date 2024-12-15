#pragma once

class FGraphics
{
	DECLARE_SINGLE(FGraphics);

public:
	void Init(HWND InHwnd);

	void RenderBegin();
	void RenderEnd();

	ComPtr<ID3D11Device> GetDevice() { return Device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return DeviceContext; }

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

private:
	HWND hwnd = {};

	// Device & SwapChain
	ComPtr<ID3D11Device> Device = nullptr;
	ComPtr<ID3D11DeviceContext> DeviceContext = nullptr;
	ComPtr<IDXGISwapChain> SwapChain = nullptr;

	// RTV
	ComPtr<ID3D11RenderTargetView> RenderTargetView;

	// Misc
	D3D11_VIEWPORT Viewport = { 0 };
};

