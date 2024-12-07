#pragma once

class FGame
{
public:
	FGame();
	virtual ~FGame();

	void Init(HWND InWindowHandle);
	void Update();
	void Render();

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();

	void CreateGeometry();
	void CreateInputLayout();

	void CreateVS();
	void CreatePS();

	void CreateSRV();

	void CreateConstantBuffer();

	void LoadShaderFromFile(const std::wstring& InPath, const std::string& InName, const std::string& InVersion, ComPtr<ID3DBlob>& OutBlob);

	void RenderBegin();
	void RenderEnd();

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

	ComPtr<ID3D11RasterizerState> RasterizerState;
	ComPtr<ID3D11SamplerState> SamplerState;
	ComPtr<ID3D11BlendState> BlendState;

	std::vector<FVertex> Vertices;
	ComPtr<ID3D11Buffer> VertexBuffer;

	std::vector<uint32> Indices;
	ComPtr<ID3D11Buffer> IndexBuffer;

	ComPtr<ID3D11InputLayout> InputLayout;

	ComPtr<ID3D11VertexShader> VertexShader;
	ComPtr<ID3DBlob> VSBlob;

	ComPtr<ID3D11PixelShader> PixelShader;
	ComPtr<ID3DBlob> PSBlob;

	ComPtr<ID3D11ShaderResourceView> ShaderResourceView0;
	ComPtr<ID3D11ShaderResourceView> ShaderResourceView1;

	FTransformData TransformData;
	ComPtr<ID3D11Buffer> ConstantBuffer;
};

