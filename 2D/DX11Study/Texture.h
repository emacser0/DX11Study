#pragma once
class FTexture
{
public:
	FTexture(ComPtr<ID3D11Device> InDevice);

	ComPtr<ID3D11ShaderResourceView> GetComPtr() const { return ShaderResourceView; }

	void Create(const std::wstring& InPath);

private:
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11ShaderResourceView> ShaderResourceView;
};

