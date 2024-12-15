#include "pch.h"
#include "Shader.h"

FShader::FShader(ComPtr<ID3D11Device> InDevice)
	: Path()
	, Name()
	, Device(InDevice)
	, Blob(nullptr)
{
}

FShader::~FShader()
{
}

void FShader::LoadShaderFromFile(const std::wstring& InPath, const std::string& InName, const std::string& InVersion)
{
#if __DEBUG
	const int32 CompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	const int32 CompileFlags = D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	Path = InPath;
	Name = InName;

	HRESULT Result = ::D3DCompileFromFile(
		InPath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		InName.c_str(),
		InVersion.c_str(),
		CompileFlags,
		0,
		Blob.GetAddressOf(),
		nullptr);
	CHECK(Result);
}

FVertexShader::FVertexShader(ComPtr<ID3D11Device> InDevice)
	: FShader(InDevice)
{
}

void FVertexShader::Create(const std::wstring& InPath, const std::string& InName, const std::string& InVersion)
{
	LoadShaderFromFile(InPath, InName, InVersion);

	HRESULT Result = Device->CreateVertexShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, VertexShader.GetAddressOf());
	CHECK(Result);
}

FPixelShader::FPixelShader(ComPtr<ID3D11Device> InDevice)
	: FShader(InDevice)
{	
}

void FPixelShader::Create(const std::wstring& InPath, const std::string& InName, const std::string& InVersion)
{
	LoadShaderFromFile(InPath, InName, InVersion);

	HRESULT Result = Device->CreatePixelShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, PixelShader.GetAddressOf());
	CHECK(Result);
}
