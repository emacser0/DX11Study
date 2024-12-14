#pragma once

#include "Geometry.h"
#include "ConstantBuffer.h"

class UGameObject
{
public:
	UGameObject(ComPtr<ID3D11Device> InDevice, ComPtr<ID3D11DeviceContext> InDeviceContext);
	virtual ~UGameObject() = default;

	void Update();
	void Render(std::shared_ptr<class FPipeline> InPipeline);

private:
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11DeviceContext> DeviceContext;

	std::shared_ptr<class FRasterizerState> RasterizerState;
	std::shared_ptr<class FSamplerState> SamplerState;
	std::shared_ptr<class FBlendState> BlendState;

	std::shared_ptr<FGeometry<struct FVertexTextureData>> Geometry;

	std::shared_ptr<class FVertexBuffer> VertexBuffer;
	std::shared_ptr<class FIndexBuffer> IndexBuffer;

	std::shared_ptr<class FInputLayout> InputLayout;

	std::shared_ptr<class FVertexShader> VertexShader;
	std::shared_ptr<class FPixelShader> PixelShader;

	std::shared_ptr<class FTexture> Texture;

	FTransformData TransformData;
	std::shared_ptr<FConstantBuffer<FTransformData>> ConstantBuffer;

	FVector3 LocalPosition;
	FVector3 LocalRotation;
	FVector3 LocalScale;
};
