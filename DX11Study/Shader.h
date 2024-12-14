#pragma once

enum EShaderScope
{
	SS_None = 0,
	SS_VertexShader = (1 << 0),
	SS_PixelShader = (1 << 1),
	SS_Both = SS_VertexShader | SS_PixelShader
};

class FShader
{
public:
	FShader(ComPtr<ID3D11Device> InDevice);
	virtual ~FShader();

	virtual void Create(const std::wstring& InPath, const std::string& InName, const std::string& InVersion) = 0;

	ComPtr<ID3DBlob> GetBlob() const { return Blob; }

protected:
	void LoadShaderFromFile(const std::wstring& InPath, const std::string& InName, const std::string& InVersion);

protected:
	std::wstring Path;
	std::string Name;
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3DBlob> Blob;
};

class FVertexShader : public FShader
{
public:
	FVertexShader(ComPtr<ID3D11Device> InDevice);
	virtual ~FVertexShader() = default;

	virtual void Create(const std::wstring& InPath, const std::string& InName, const std::string& InVersion) override;

	ComPtr<ID3D11VertexShader> GetComPtr() const { return VertexShader; }

protected:
	ComPtr<ID3D11VertexShader> VertexShader;
};

class FPixelShader : public FShader
{
public:
	FPixelShader(ComPtr<ID3D11Device> InDevice);
	virtual ~FPixelShader() = default;

	virtual void Create(const std::wstring& InPath, const std::string& InName, const std::string& InVersion) override;

	ComPtr<ID3D11PixelShader> GetComPtr() const { return PixelShader; }

protected:
	ComPtr<ID3D11PixelShader> PixelShader;
};
