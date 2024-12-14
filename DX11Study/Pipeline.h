#pragma once

#include "ConstantBuffer.h"
#include "Shader.h"

struct FPipelineInfo
{
	std::shared_ptr<class FInputLayout> InputLayout;
	std::shared_ptr<class FVertexShader> VertexShader;
	std::shared_ptr<class FPixelShader> PixelShader;
	std::shared_ptr<class FRasterizerState> RasterizerState;
	std::shared_ptr<class FBlendState> BlendState;
	D3D11_PRIMITIVE_TOPOLOGY Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

class FPipeline
{
public:
	FPipeline(ComPtr<ID3D11Device> InDevice, ComPtr<ID3D11DeviceContext> InDeviceContext);
	virtual ~FPipeline() = default;

	void UpdatePipeline(const FPipelineInfo& InInfo);

	void SetVertexBuffer(std::shared_ptr<class FVertexBuffer> InVertexBuffer);
	void SetIndexBuffer(std::shared_ptr<class FIndexBuffer> InIndexBuffer);

	template <typename T>
	void SetConstantBuffer(uint32 InSlot, uint32 InScope, std::shared_ptr<FConstantBuffer<T>> InConstantBuffer)
	{
		if (InScope & SS_VertexShader)
		{
			DeviceContext->VSSetConstantBuffers(InSlot, 1, InConstantBuffer->GetComPtr().GetAddressOf());
		}

		if (InScope & SS_PixelShader)
		{
			DeviceContext->PSSetConstantBuffers(InSlot, 1, InConstantBuffer->GetComPtr().GetAddressOf());
		}
	}

	void SetTexture(uint32 InSlot, uint32 InScope, std::shared_ptr<class FTexture> InTexture);
	void SetSamplerState(uint32 InSlot, uint32 InScope, std::shared_ptr<class FSamplerState> InSamplerState);

	void Draw(uint32 InVertexCount, uint32 InStartVertexLocation);
	void DrawIndexed(uint32 InIndexCount, uint32 InStartIndexLocation, uint32 InBaseVertexLocation);

private:
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11DeviceContext> DeviceContext;
};
