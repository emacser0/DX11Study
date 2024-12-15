#pragma once
class FIndexBuffer
{
public:
	FIndexBuffer(ComPtr<ID3D11Device> InDevice);
	virtual ~FIndexBuffer();

	ComPtr<ID3D11Buffer> GetComPtr() const { return Buffer; }

	uint32 GetStride() const { return Stride; }
	uint32 GetOffset() const { return Offset; }
	uint32 GetCount() const { return Count; }

	void Create(const std::vector<uint32>& InIndices);

private:
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11Buffer> Buffer;

	uint32 Stride;
	uint32 Offset;
	uint32 Count;
};

