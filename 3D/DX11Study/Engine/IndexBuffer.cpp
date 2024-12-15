#include "pch.h"
#include "IndexBuffer.h"

FIndexBuffer::FIndexBuffer()
{

}

FIndexBuffer::~FIndexBuffer()
{

}

void FIndexBuffer::Create(const std::vector<uint32>& InIndices)
{
	Stride = sizeof(uint32);
	Count = static_cast<uint32>(InIndices.size());

	D3D11_BUFFER_DESC Desc;
	ZeroMemory(&Desc, sizeof(Desc));
	Desc.Usage = D3D11_USAGE_IMMUTABLE;
	Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	Desc.ByteWidth = (uint32)(Stride * Count);

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = InIndices.data();

	HRESULT Result = DEVICE->CreateBuffer(&Desc, &data, IndexBuffer.GetAddressOf());
	CHECK(Result);
}
