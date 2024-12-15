#pragma once

template <typename T>
class FConstantBuffer
{
public:
	FConstantBuffer(ComPtr<ID3D11Device> InDevice, ComPtr<ID3D11DeviceContext> InDeviceContext)
		: Device(InDevice)
		, DeviceContext(InDeviceContext)
		, Buffer(nullptr) { }
	virtual ~FConstantBuffer() = default;

	ComPtr<ID3D11Buffer> GetComPtr() const { return Buffer; }

	void Create()
	{
		D3D11_BUFFER_DESC BufferDesc;
		ZeroMemory(&BufferDesc, sizeof(BufferDesc));
		BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		BufferDesc.ByteWidth = sizeof(T);
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT Result = Device->CreateBuffer(&BufferDesc, nullptr, Buffer.GetAddressOf());
		CHECK(Result);
	}

	void CopyData(const T& Data)
	{
		D3D11_MAPPED_SUBRESOURCE SubResource;
		ZeroMemory(&SubResource, sizeof(SubResource));

		DeviceContext->Map(Buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &SubResource);
		memcpy(SubResource.pData, &Data, sizeof(T));
		DeviceContext->Unmap(Buffer.Get(), 0);
	}

private:
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11DeviceContext> DeviceContext;
	ComPtr<ID3D11Buffer> Buffer;
};

