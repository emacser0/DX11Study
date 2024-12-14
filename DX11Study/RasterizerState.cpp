#include "pch.h"
#include "RasterizerState.h"

FRasterizerState::FRasterizerState(ComPtr<ID3D11Device> InDevice)
	: Device(InDevice)
	, RasterizerState(nullptr)
{
}

void FRasterizerState::Create()
{
	D3D11_RASTERIZER_DESC RasterizerDesc{};
	ZeroMemory(&RasterizerDesc, sizeof(RasterizerDesc));
	RasterizerDesc.FillMode = D3D11_FILL_SOLID;
	RasterizerDesc.CullMode = D3D11_CULL_NONE;
	RasterizerDesc.FrontCounterClockwise = false;

	HRESULT Result = Device->CreateRasterizerState(&RasterizerDesc, RasterizerState.GetAddressOf());
	CHECK(Result);
}
