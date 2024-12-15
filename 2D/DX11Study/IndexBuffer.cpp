#include "pch.h"
#include "IndexBuffer.h"

FIndexBuffer::FIndexBuffer(ComPtr<ID3D11Device> InDevice)
	: Device(InDevice)
	, Buffer(nullptr)
	, Stride(0)
	, Offset(0)
	, Count(0)
{
}

FIndexBuffer::~FIndexBuffer()
{
}

void FIndexBuffer::Create(const std::vector<uint32>& InIndices)
{
	Stride = sizeof(uint32);
	Offset = 0;
	Count = InIndices.size();

	D3D11_BUFFER_DESC Desc{};
	ZeroMemory(&Desc, sizeof(Desc));
	Desc.Usage = D3D11_USAGE_IMMUTABLE;
	Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	Desc.ByteWidth = static_cast<uint32>(Stride * Count);

	D3D11_SUBRESOURCE_DATA Data;
	ZeroMemory(&Data, sizeof(Data));
	Data.pSysMem = InIndices.data();

	HRESULT Result = Device->CreateBuffer(&Desc, &Data, Buffer.GetAddressOf());
	CHECK(Result);
}
