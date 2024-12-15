#include "pch.h"
#include "Texture.h"

FTexture::FTexture() : Super(EResourceType::Texture)
{

}

FTexture::~FTexture()
{

}

void FTexture::Load(const std::wstring& path)
{
	DirectX::TexMetadata Metadata;
	HRESULT Result = ::LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, &Metadata, Image);
	CHECK(Result);

	Result = ::CreateShaderResourceView(DEVICE.Get(), Image.GetImages(), Image.GetImageCount(), Metadata, ShaderResourveView.GetAddressOf());
	CHECK(Result);
	
	Size.x = Metadata.width;
	Size.y = Metadata.height;
}

