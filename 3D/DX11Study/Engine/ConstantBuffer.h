#pragma once

template<typename T>
class FConstantBuffer
{
public:
	FConstantBuffer() { }
	~FConstantBuffer() { }

	ComPtr<ID3D11Buffer> GetComPtr() { return ConstantBuffer; }

	void Create()
	{
		D3D11_BUFFER_DESC Desc;
		ZeroMemory(&Desc, sizeof(Desc));
		Desc.Usage = D3D11_USAGE_DYNAMIC; // CPU_Write + GPU_Read
		Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		Desc.ByteWidth = sizeof(T);
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT Result = DEVICE->CreateBuffer(&Desc, nullptr, ConstantBuffer.GetAddressOf());
		CHECK(Result);
	}

	void CopyData(const T& InData)
	{
		D3D11_MAPPED_SUBRESOURCE subResource;
		ZeroMemory(&subResource, sizeof(subResource));

		DC->Map(ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		::memcpy(subResource.pData, &InData, sizeof(InData));
		DC->Unmap(ConstantBuffer.Get(), 0);
	}

private:
	ComPtr<ID3D11Buffer> ConstantBuffer;
};
