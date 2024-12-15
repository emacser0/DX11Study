#pragma once
#include "Pass.h"
#include "Technique.h"

struct FShaderDesc
{
	ComPtr<ID3DBlob> Blob;
	ComPtr<ID3DX11Effect> Effect;
};

class FShader
{
public:
	friend struct FPass;

public:
	FShader(const std::wstring& InFile);
	~FShader();

	std::wstring GetFile() { return File; }
	ComPtr<ID3DX11Effect> Effect() { return ShaderDesc.Effect; }

	void Draw(UINT InTechnique, UINT InPass, UINT InVertexCount, UINT InStartVertexLocation = 0);
	void DrawIndexed(UINT InTechnique, UINT InPass, UINT InIndexCount, UINT InStartIndexLocation = 0, INT InBaseVertexLocation = 0);
	void DrawInstanced(UINT InTechnique, UINT InPass, UINT InVertexCountPerInstance, UINT InInstanceCount, UINT InStartVertexLocation = 0, UINT InStartInstanceLocation = 0);
	void DrawIndexedInstanced(UINT InTechnique, UINT InPass, UINT InIndexCountPerInstance, UINT InInstanceCount, UINT startIndexLocation = 0, INT InBaseVertexLocation = 0, UINT InStartInstanceLocation = 0);

	void Dispatch(UINT InTechnique, UINT InPass, UINT InX, UINT InY, UINT InZ);

	ComPtr<ID3DX11EffectVariable> GetVariable(const std::string& InName);
	ComPtr<ID3DX11EffectScalarVariable> GetScalar(const std::string& InName);
	ComPtr<ID3DX11EffectVectorVariable> GetVector(const std::string& InName);
	ComPtr<ID3DX11EffectMatrixVariable> GetMatrix(const std::string& InName);
	ComPtr<ID3DX11EffectStringVariable> GetString(const std::string& InName);
	ComPtr<ID3DX11EffectShaderResourceVariable> GetSRV(const std::string& InName);
	ComPtr<ID3DX11EffectRenderTargetViewVariable> GetRTV(const std::string& InName);
	ComPtr<ID3DX11EffectDepthStencilViewVariable> GetDSV(const std::string& InName);
	ComPtr<ID3DX11EffectUnorderedAccessViewVariable> GetUAV(const std::string& InName);
	ComPtr<ID3DX11EffectConstantBuffer> GetConstantBuffer(const std::string& InName);
	ComPtr<ID3DX11EffectShaderVariable> GetShader(const std::string& InName);
	ComPtr<ID3DX11EffectBlendVariable> GetBlend(const std::string& InName);
	ComPtr<ID3DX11EffectDepthStencilVariable> GetDepthStencil(const std::string& InName);
	ComPtr<ID3DX11EffectRasterizerVariable> GetRasterizer(const std::string& InName);
	ComPtr<ID3DX11EffectSamplerVariable> GetSampler(const std::string& InName);

private:
	void CreateEffect();
	ComPtr<ID3D11InputLayout> CreateInputLayout(ComPtr<ID3DBlob> InFXBlob, D3DX11_EFFECT_SHADER_DESC* InEffectVsDesc, std::vector<D3D11_SIGNATURE_PARAMETER_DESC>& InParams);

private:
	std::wstring File;
	FShaderDesc ShaderDesc;
	D3DX11_EFFECT_DESC EffectDesc;
	std::shared_ptr<FStateBlock> InitialStateBlock;
	std::vector<FTechnique> Techniques;
};

class ShaderManager
{
public:
	static FShaderDesc GetEffect(const std::wstring& InFileName);

private:
	static unordered_map<std::wstring, FShaderDesc> Shaders;
};