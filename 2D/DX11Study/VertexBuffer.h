#pragma once

class FVertexBuffer
{
public:
	FVertexBuffer(ComPtr<ID3D11Device> InDevice);
	virtual ~FVertexBuffer();

	ComPtr<ID3D11Buffer> GetComPtr() const { return Buffer; }

	uint32 GetStride() const { return Stride; }
	uint32 GetOffset() const { return Offset; }
	uint32 GetCount() const { return Count; }

	template <typename T>
	void Create(const std::vector<T>& InVertices)
	{
		Stride = sizeof(T);
		Offset = 0;
		Count = InVertices.size();

		D3D11_BUFFER_DESC Desc{};
		ZeroMemory(&Desc, sizeof(Desc));
		Desc.Usage = D3D11_USAGE_IMMUTABLE;
		Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		Desc.ByteWidth = static_cast<uint32>(Stride * Count);

		D3D11_SUBRESOURCE_DATA Data;
		ZeroMemory(&Data, sizeof(Data));
		Data.pSysMem = InVertices.data();

		HRESULT Result = Device->CreateBuffer(&Desc, &Data, Buffer.GetAddressOf());
		CHECK(Result);
	}

private:
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11Buffer> Buffer;

	uint32 Stride;
	uint32 Offset;
	uint32 Count;
};

