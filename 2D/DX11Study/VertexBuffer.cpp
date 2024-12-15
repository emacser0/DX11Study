#include "pch.h"
#include "VertexBuffer.h"

FVertexBuffer::FVertexBuffer(ComPtr<ID3D11Device> InDevice)
	: Device(InDevice)
	, Buffer(nullptr)
	, Stride(0)
	, Offset(0)
	, Count(0)
{
}

FVertexBuffer::~FVertexBuffer()
{
}
