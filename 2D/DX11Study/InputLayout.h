#pragma once
class FInputLayout
{
public:
	FInputLayout(ComPtr<ID3D11Device> InDevice);
	virtual ~FInputLayout();

	ComPtr<ID3D11InputLayout> GetComPtr() const { return InputLayout; }

	void Create(const std::vector<D3D11_INPUT_ELEMENT_DESC>& Descs, ComPtr<ID3DBlob> InBlob);

private:
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11InputLayout> InputLayout;
};

