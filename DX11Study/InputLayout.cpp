#include "pch.h"
#include "InputLayout.h"

FInputLayout::FInputLayout(ComPtr<ID3D11Device> InDevice)
	: Device(InDevice)
	, InputLayout(nullptr)
{
}

FInputLayout::~FInputLayout()
{
}

void FInputLayout::Create(const std::vector<D3D11_INPUT_ELEMENT_DESC>& Descs, ComPtr<ID3DBlob> InBlob)
{
	const int32 Count = Descs.size();
	Device->CreateInputLayout(Descs.data(), Count, InBlob->GetBufferPointer(), InBlob->GetBufferSize(), InputLayout.GetAddressOf());
}
