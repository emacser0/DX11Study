#pragma once
class FGraphics
{
public:
	FGraphics(HWND InWindowHandle);

	void RenderBegin();
	void RenderEnd();

	ComPtr<ID3D11Device> GetDevice() const { return Device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() const { return DeviceContext; }

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

private:
	HWND WindowHandle;
	uint32 Width;
	uint32 Height;

	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11DeviceContext> DeviceContext;
	ComPtr<IDXGISwapChain> SwapChain;

	ComPtr<ID3D11RenderTargetView> RenderTargetView;

	D3D11_VIEWPORT Viewport;
	float ClearColor[4];
};

