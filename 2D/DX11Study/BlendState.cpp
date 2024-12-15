#include "pch.h"
#include "BlendState.h"

FBlendState::FBlendState(ComPtr<ID3D11Device> InDevice)
	: Device(InDevice)
	, BlendState(nullptr)
	, BlendFactor(0.0f)
	, SamplerMask(0xFFFFFFFF)
{
}

void FBlendState::Create(D3D11_RENDER_TARGET_BLEND_DESC InDesc, float InFactor)
{
	BlendFactor = InFactor;

	D3D11_BLEND_DESC BlendDesc{};
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = false;
	BlendDesc.IndependentBlendEnable = false;
	BlendDesc.RenderTarget[0] = InDesc;

	HRESULT Result = Device->CreateBlendState(&BlendDesc, BlendState.GetAddressOf());
	CHECK(Result);
}
