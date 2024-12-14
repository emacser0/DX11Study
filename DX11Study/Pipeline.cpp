#include "pch.h"
#include "Pipeline.h"
#include "InputLayout.h"
#include "RasterizerState.h"
#include "SamplerState.h"
#include "BlendState.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "SamplerState.h"

FPipeline::FPipeline(ComPtr<ID3D11DeviceContext> InDeviceContext)
	: DeviceContext(InDeviceContext)
{

}

void FPipeline::UpdatePipeline(const FPipelineInfo& InInfo)
{
	// IA
	DeviceContext->IASetInputLayout(InInfo.InputLayout->GetComPtr().Get());
	DeviceContext->IASetPrimitiveTopology(InInfo.Topology);

	// VS
	DeviceContext->VSSetShader(InInfo.VertexShader->GetComPtr().Get(), nullptr, 0);

	// RS
	DeviceContext->RSSetState(InInfo.RasterizerState->GetComPtr().Get());

	// PS
	DeviceContext->PSSetShader(InInfo.PixelShader->GetComPtr().Get(), nullptr, 0);

	// OM
	DeviceContext->OMSetBlendState(InInfo.BlendState->GetComPtr().Get(), InInfo.BlendState->GetBlendFactor(), InInfo.BlendState->GetSamplerMask());
}

void FPipeline::SetVertexBuffer(std::shared_ptr<FVertexBuffer> InVertexBuffer)
{
	uint32 Stride = InVertexBuffer->GetStride();
	uint32 Offset = InVertexBuffer->GetOffset();

	DeviceContext->IASetVertexBuffers(0, 1, InVertexBuffer->GetComPtr().GetAddressOf(), &Stride, &Offset);
}

void FPipeline::SetIndexBuffer(std::shared_ptr<FIndexBuffer> InIndexBuffer)
{
	DeviceContext->IASetIndexBuffer(InIndexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
}

void FPipeline::SetTexture(uint32 InSlot, uint32 InScope, std::shared_ptr<FTexture> InTexture)
{
	if (InScope & SS_VertexShader)
	{
		DeviceContext->VSSetShaderResources(InSlot, 1, InTexture->GetComPtr().GetAddressOf());
	}
	
	if (InScope & SS_PixelShader)
	{
		DeviceContext->PSSetShaderResources(InSlot, 1, InTexture->GetComPtr().GetAddressOf());
	}
}

void FPipeline::SetSamplerState(uint32 InSlot, uint32 InScope, std::shared_ptr<FSamplerState> InSamplerState)
{
	if (InScope & SS_VertexShader)
	{
		DeviceContext->VSSetSamplers(InSlot, 1, InSamplerState->GetComPtr().GetAddressOf());
	}
	
	if (InScope & SS_PixelShader)
	{
		DeviceContext->PSSetSamplers(InSlot, 1, InSamplerState->GetComPtr().GetAddressOf());
	}
}

void FPipeline::Draw(uint32 InVertexCount, uint32 InStartVertexLocation)
{
	DeviceContext->Draw(InVertexCount, InStartVertexLocation);
}

void FPipeline::DrawIndexed(uint32 InIndexCount, uint32 InStartIndexLocation, uint32 InBaseVertexLocation)
{
	DeviceContext->DrawIndexed(InIndexCount, InStartIndexLocation, InBaseVertexLocation);
}

