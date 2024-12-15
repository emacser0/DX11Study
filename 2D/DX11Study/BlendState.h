#pragma once

class FBlendState
{
public:
	FBlendState(ComPtr<ID3D11Device> InDevice);
	virtual ~FBlendState() = default;

	ComPtr<ID3D11BlendState> GetComPtr() const { return BlendState; }

	const float* GetBlendFactor() const { return &BlendFactor; }
	uint32 GetSamplerMask() const { return SamplerMask; }

	void Create(D3D11_RENDER_TARGET_BLEND_DESC InDesc =
		{
			true,
			D3D11_BLEND_SRC_ALPHA,
			D3D11_BLEND_INV_SRC_ALPHA,
			D3D11_BLEND_OP_ADD,
			D3D11_BLEND_ONE,
			D3D11_BLEND_ZERO,
			D3D11_BLEND_OP_ADD,
			D3D11_COLOR_WRITE_ENABLE_ALL
		},
		float InFactor = 0.0f);

private:
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11BlendState> BlendState;

	float BlendFactor;
	uint32 SamplerMask;
};
