#pragma once

#include "Geometry.h"
#include "VertexData.h"

class FGame
{
public:
	FGame();
	virtual ~FGame();

	void Init(HWND InWindowHandle);
	void Update();
	void Render();

private:
	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();

	void CreateGeometry();
	void CreateInputLayout();

	void CreateVS();
	void CreatePS();

	void CreateSRV();

	void CreateConstantBuffer();

private:
	std::shared_ptr<class FGraphics> Graphics;

	ComPtr<ID3D11RasterizerState> RasterizerState;
	ComPtr<ID3D11SamplerState> SamplerState;
	ComPtr<ID3D11BlendState> BlendState;

	std::shared_ptr<FGeometry<FVertexTextureData>> Geometry;

	std::shared_ptr<class FVertexBuffer> VertexBuffer;
	std::shared_ptr<class FIndexBuffer> IndexBuffer;

	std::shared_ptr<class FInputLayout> InputLayout;

	std::shared_ptr<class FVertexShader> VertexShader;
	std::shared_ptr<class FPixelShader> PixelShader;

	ComPtr<ID3D11ShaderResourceView> ShaderResourceView0;
	ComPtr<ID3D11ShaderResourceView> ShaderResourceView1;

	FTransformData TransformData;
	ComPtr<ID3D11Buffer> ConstantBuffer;

	FVector3 LocalPosition;
	FVector3 LocalRotation;
	FVector3 LocalScale;
};

