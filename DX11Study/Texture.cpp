#include "pch.h"
#include "Texture.h"

FTexture::FTexture(ComPtr<ID3D11Device> InDevice)
	: Device(InDevice)
	, ShaderResourceView(nullptr)
{

}

void FTexture::Create(const std::wstring& InPath)
{
	TexMetadata Metadata;
	ScratchImage Image;
	HRESULT Result = ::LoadFromWICFile(InPath.c_str(), WIC_FLAGS_NONE, &Metadata, Image);
	CHECK(Result);

	Result = ::CreateShaderResourceView(Device.Get(), Image.GetImages(), Image.GetImageCount(), Metadata, ShaderResourceView.GetAddressOf());
	CHECK(Result);
}
