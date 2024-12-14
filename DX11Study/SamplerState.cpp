#include "pch.h"
#include "SamplerState.h"

FSamplerState::FSamplerState(ComPtr<ID3D11Device> InDevice)
	: Device(InDevice)
	, SamplerState(nullptr)
{
}

void FSamplerState::Create()
{
	D3D11_SAMPLER_DESC SamplerDesc{};
	ZeroMemory(&SamplerDesc, sizeof(SamplerDesc));

	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	SamplerDesc.BorderColor[0] = 1.0f;
	SamplerDesc.BorderColor[1] = 0.0f;
	SamplerDesc.BorderColor[2] = 0.0f;
	SamplerDesc.BorderColor[3] = 1.0f;
	SamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	SamplerDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	SamplerDesc.MaxAnisotropy = 16;
	SamplerDesc.MaxLOD = FLT_MAX;
	SamplerDesc.MinLOD = FLT_MIN;
	SamplerDesc.MipLODBias = 0;

	HRESULT Result = Device->CreateSamplerState(&SamplerDesc, SamplerState.GetAddressOf());
	CHECK(Result);
}
