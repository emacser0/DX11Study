#pragma once

class FRasterizerState
{
public:
	FRasterizerState(ComPtr<ID3D11Device> InDevice);
	virtual ~FRasterizerState() = default;

	ComPtr<ID3D11RasterizerState> GetComPtr() const { return RasterizerState; }

	void Create();

private:
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11RasterizerState> RasterizerState;
};
