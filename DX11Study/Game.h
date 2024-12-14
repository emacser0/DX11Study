#pragma once

#include "Geometry.h"
#include "VertexData.h"
#include "ConstantBuffer.h"

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

	std::shared_ptr<class FRasterizerState> RasterizerState;
	std::shared_ptr<class FSamplerState> SamplerState;
	std::shared_ptr<class FBlendState> BlendState;

	std::shared_ptr<FGeometry<FVertexTextureData>> Geometry;

	std::shared_ptr<class FVertexBuffer> VertexBuffer;
	std::shared_ptr<class FIndexBuffer> IndexBuffer;

	std::shared_ptr<class FInputLayout> InputLayout;

	std::shared_ptr<class FVertexShader> VertexShader;
	std::shared_ptr<class FPixelShader> PixelShader;

	std::shared_ptr<class FTexture> Texture0;
	std::shared_ptr<class FTexture> Texture1;

	FTransformData TransformData;
	std::shared_ptr<FConstantBuffer<FTransformData>> ConstantBuffer;

	FVector3 LocalPosition;
	FVector3 LocalRotation;
	FVector3 LocalScale;
};

