#pragma once
#include "ResourceBase.h"

class FTexture : public FResourceBase
{
	using Super = FResourceBase;
public:
	FTexture();
	~FTexture();

	ComPtr<ID3D11ShaderResourceView> GetComPtr() { return ShaderResourveView; }

	virtual void Load(const std::wstring& path) override;

	Vec2 GetSize() { return Size; }

	const DirectX::ScratchImage& GetInfo() { return Image; }

private:
	ComPtr<ID3D11ShaderResourceView> ShaderResourveView;
	Vec2 Size = {0.f, 0.f};
	DirectX::ScratchImage Image = {};
};

