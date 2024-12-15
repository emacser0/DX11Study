#pragma once

class FVertexBuffer
{
public:
	FVertexBuffer();
	~FVertexBuffer();

	ComPtr<ID3D11Buffer> GetComPtr() { return VertexBuffer; }
	uint32 GetStride() { return Stride; }
	uint32 GetOffset() { return Offset; }
	uint32 GetCount() { return Count; }

	template<typename T>
	void Create(const std::vector<T>& InVertices)
	{
		Stride = sizeof(T);
		Count = static_cast<uint32>(InVertices.size());

		D3D11_BUFFER_DESC Desc;
		ZeroMemory(&Desc, sizeof(Desc));
		Desc.Usage = D3D11_USAGE_IMMUTABLE;
		Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		Desc.ByteWidth = (uint32)(Stride * Count);

		D3D11_SUBRESOURCE_DATA Data;
		ZeroMemory(&Data, sizeof(Data));
		Data.pSysMem = InVertices.data();

		HRESULT Result = DEVICE->CreateBuffer(&Desc, &Data, VertexBuffer.GetAddressOf());
		CHECK(Result);
	}

private:
	ComPtr<ID3D11Buffer> VertexBuffer;

	uint32 Stride = 0;
	uint32 Offset = 0;
	uint32 Count = 0;
};
