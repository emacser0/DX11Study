#pragma once

class FSamplerState
{
public:
	FSamplerState(ComPtr<ID3D11Device> InDevice);
	virtual ~FSamplerState() = default;

	ComPtr<ID3D11SamplerState> GetComPtr() const { return SamplerState; }

	void Create();

private:
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11SamplerState> SamplerState;
};
