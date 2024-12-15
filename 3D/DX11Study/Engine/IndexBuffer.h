#pragma once

class FIndexBuffer
{
public:
	FIndexBuffer();
	~FIndexBuffer();

	ComPtr<ID3D11Buffer> GetComPtr() { return IndexBuffer; }
	uint32 GetStride() { return Stride; }
	uint32 GetOffset() { return Offset; }
	uint32 GetCount() { return Count; }

	void Create(const std::vector<uint32>& InIndices);

private:
	ComPtr<ID3D11Buffer> IndexBuffer;

	uint32 Stride = 0;
	uint32 Offset = 0;
	uint32 Count = 0;
};

