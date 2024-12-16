#include "pch.h"
#include "Shader.h"
#include "Utils.h"

FShader::FShader(const std::wstring& InFile) : File(L"..\\Shaders\\" + InFile)
{
	InitialStateBlock = std::make_shared<FStateBlock>();
	{
		DC->RSGetState(InitialStateBlock->RSRasterizerState.GetAddressOf());
		DC->OMGetBlendState(InitialStateBlock->OMBlendState.GetAddressOf(), InitialStateBlock->OMBlendFactor, &InitialStateBlock->OMSampleMask);
		DC->OMGetDepthStencilState(InitialStateBlock->OMDepthStencilState.GetAddressOf(), &InitialStateBlock->OMStencilRef);
	}

	CreateEffect();
}

FShader::~FShader()
{
	
}

void FShader::CreateEffect()
{
	ShaderDesc = FShaderManager::GetEffect(File);

	ShaderDesc.Effect->GetDesc(&EffectDesc);
	for (UINT t = 0; t < EffectDesc.Techniques; t++)
	{
		FTechnique Technique;
		Technique.Technique = ShaderDesc.Effect->GetTechniqueByIndex(t);
		Technique.Technique->GetDesc(&Technique.Desc);
		Technique.Name = FUtils::ToWString(Technique.Desc.Name);

		for (UINT p = 0; p < Technique.Desc.Passes; p++)
		{
			FPass Pass;
			Pass.Pass = Technique.Technique->GetPassByIndex(p);
			Pass.Pass->GetDesc(&Pass.Desc);
			Pass.Name = FUtils::ToWString(Pass.Desc.Name);
			Pass.Pass->GetVertexShaderDesc(&Pass.PassVsDesc);
			Pass.PassVsDesc.pShaderVariable->GetShaderDesc(Pass.PassVsDesc.ShaderIndex, &Pass.EffectVsDesc);

			for (UINT s = 0; s < Pass.EffectVsDesc.NumInputSignatureEntries; s++)
			{
				D3D11_SIGNATURE_PARAMETER_DESC Desc;

				HRESULT Result = Pass.PassVsDesc.pShaderVariable->GetInputSignatureElementDesc(Pass.PassVsDesc.ShaderIndex, s, &Desc);
				CHECK(Result);

				Pass.signatureDescs.push_back(Desc);
			}

			Pass.InputLayout = CreateInputLayout(ShaderDesc.Blob, &Pass.EffectVsDesc, Pass.signatureDescs);
			Pass.StateBlock = InitialStateBlock;

			Technique.Passes.push_back(Pass);
		}

		Techniques.push_back(Technique);
	}

	for (UINT i = 0; i < EffectDesc.ConstantBuffers; i++)
	{
		ID3DX11EffectConstantBuffer* iBuffer;
		iBuffer = ShaderDesc.Effect->GetConstantBufferByIndex(i);

		D3DX11_EFFECT_VARIABLE_DESC vDesc;
		iBuffer->GetDesc(&vDesc);
	}

	for (UINT i = 0; i < EffectDesc.GlobalVariables; i++)
	{
		ID3DX11EffectVariable* EffectVariable;
		EffectVariable = ShaderDesc.Effect->GetVariableByIndex(i);

		D3DX11_EFFECT_VARIABLE_DESC vDesc;
		EffectVariable->GetDesc(&vDesc);
	}
}

ComPtr<ID3D11InputLayout> FShader::CreateInputLayout(ComPtr<ID3DBlob> InFXBlob, D3DX11_EFFECT_SHADER_DESC* InEffectVsDesc, std::vector<D3D11_SIGNATURE_PARAMETER_DESC>& Params)
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputLayoutDesc;

	for (D3D11_SIGNATURE_PARAMETER_DESC& ParamDesc : Params)
	{
		D3D11_INPUT_ELEMENT_DESC ElementDesc;
		ElementDesc.SemanticName = ParamDesc.SemanticName;
		ElementDesc.SemanticIndex = ParamDesc.SemanticIndex;
		ElementDesc.InputSlot = 0;
		ElementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		ElementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		ElementDesc.InstanceDataStepRate = 0;

		if (ParamDesc.Mask == 1)
		{
			if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				ElementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				ElementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				ElementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (ParamDesc.Mask <= 3)
		{
			if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				ElementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				ElementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				ElementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (ParamDesc.Mask <= 7)
		{
			if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				ElementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				ElementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				ElementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if (ParamDesc.Mask <= 15)
		{
			if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				ElementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				ElementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				ElementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		std::string Name = ParamDesc.SemanticName;
		std::transform(Name.begin(), Name.end(), Name.begin(), toupper);

		if (Name == "POSITION")
		{
			ElementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}

		if (FUtils::StartsWith(Name, "INST"))
		{
			ElementDesc.InputSlot = 1;
			ElementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			ElementDesc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
			ElementDesc.InstanceDataStepRate = 1;
		}

		if (FUtils::StartsWith(Name, "SV_") == false)
			InputLayoutDesc.push_back(ElementDesc);
	}

	const void* Code = InEffectVsDesc->pBytecode;
	UINT CodeSize = InEffectVsDesc->BytecodeLength;

	if (InputLayoutDesc.size() > 0)
	{
		ComPtr<ID3D11InputLayout> InputLayout;

		HRESULT Result = DEVICE->CreateInputLayout
		(
			&InputLayoutDesc[0]
			, InputLayoutDesc.size()
			, Code
			, CodeSize
			, InputLayout.GetAddressOf()
		);

		CHECK(Result);

		return InputLayout;
	}

	return nullptr;
}

void FShader::Draw(UINT InTechnique, UINT InPass, UINT InVertexCount, UINT InStartVertexLocation)
{
	Techniques[InTechnique].Passes[InPass].Draw(InVertexCount, InStartVertexLocation);
}

void FShader::DrawIndexed(UINT InTechnique, UINT InPass, UINT InIndexCount, UINT InStartIndexLocation, INT InBaseVertexLocation)
{
	Techniques[InTechnique].Passes[InPass].DrawIndexed(InIndexCount, InStartIndexLocation, InBaseVertexLocation);
}

void FShader::DrawInstanced(UINT InTechnique, UINT InPass, UINT InVertexCountPerInstance, UINT InInstanceCount, UINT InStartVertexLocation, UINT InStartInstanceLocation)
{
	Techniques[InTechnique].Passes[InPass].DrawInstanced(InVertexCountPerInstance, InInstanceCount, InStartVertexLocation, InStartInstanceLocation);
}

void FShader::DrawIndexedInstanced(UINT InTechnique, UINT InPass, UINT InIndexCountPerInstance, UINT InInstanceCount, UINT InStartIndexLocation, INT InBaseVertexLocation, UINT InStartInstanceLocation)
{
	Techniques[InTechnique].Passes[InPass].DrawIndexedInstanced(InIndexCountPerInstance, InInstanceCount, InStartIndexLocation, InBaseVertexLocation, InStartInstanceLocation);
}

void FShader::Dispatch(UINT InTechnique, UINT InPass, UINT InX, UINT InY, UINT InZ)
{
	Techniques[InTechnique].Passes[InPass].Dispatch(InX, InY, InZ);
}

ComPtr<ID3DX11EffectVariable> FShader::GetVariable(const std::string& InName)
{
	return ShaderDesc.Effect->GetVariableByName(InName.c_str());
}

ComPtr<ID3DX11EffectScalarVariable> FShader::GetScalar(const std::string& InName)
{
	return ShaderDesc.Effect->GetVariableByName(InName.c_str())->AsScalar();
}

ComPtr<ID3DX11EffectVectorVariable> FShader::GetVector(const std::string& InName)
{
	return ShaderDesc.Effect->GetVariableByName(InName.c_str())->AsVector();
}

ComPtr<ID3DX11EffectMatrixVariable> FShader::GetMatrix(const std::string& InName)
{
	return ShaderDesc.Effect->GetVariableByName(InName.c_str())->AsMatrix();
}

ComPtr<ID3DX11EffectStringVariable> FShader::GetString(const std::string& InName)
{
	return ShaderDesc.Effect->GetVariableByName(InName.c_str())->AsString();
}

ComPtr<ID3DX11EffectShaderResourceVariable> FShader::GetSRV(const std::string& InName)
{
	return ShaderDesc.Effect->GetVariableByName(InName.c_str())->AsShaderResource();
}

ComPtr<ID3DX11EffectRenderTargetViewVariable> FShader::GetRTV(const std::string& InName)
{
	return ShaderDesc.Effect->GetVariableByName(InName.c_str())->AsRenderTargetView();
}

ComPtr<ID3DX11EffectDepthStencilViewVariable> FShader::GetDSV(const std::string& InName)
{
	return ShaderDesc.Effect->GetVariableByName(InName.c_str())->AsDepthStencilView();
}

ComPtr<ID3DX11EffectConstantBuffer> FShader::GetConstantBuffer(const std::string& InName)
{
	return ShaderDesc.Effect->GetConstantBufferByName(InName.c_str());
}

ComPtr<ID3DX11EffectShaderVariable> FShader::GetShader(const std::string& InName)
{
	return ShaderDesc.Effect->GetVariableByName(InName.c_str())->AsShader();
}

ComPtr<ID3DX11EffectBlendVariable> FShader::GetBlend(const std::string& InName)
{
	return ShaderDesc.Effect->GetVariableByName(InName.c_str())->AsBlend();
}

ComPtr<ID3DX11EffectDepthStencilVariable> FShader::GetDepthStencil(const std::string& InName)
{
	return ShaderDesc.Effect->GetVariableByName(InName.c_str())->AsDepthStencil();
}

ComPtr<ID3DX11EffectRasterizerVariable> FShader::GetRasterizer(const std::string& InName)
{
	return ShaderDesc.Effect->GetVariableByName(InName.c_str())->AsRasterizer();
}

ComPtr<ID3DX11EffectSamplerVariable> FShader::GetSampler(const std::string& InName)
{
	return ShaderDesc.Effect->GetVariableByName(InName.c_str())->AsSampler();
}

ComPtr<ID3DX11EffectUnorderedAccessViewVariable> FShader::GetUAV(const std::string& InName)
{
	return ShaderDesc.Effect->GetVariableByName(InName.c_str())->AsUnorderedAccessView();
}

unordered_map<std::wstring, FShaderDesc> FShaderManager::Shaders;

FShaderDesc FShaderManager::GetEffect(const std::wstring& InFileName)
{
	if (Shaders.count(InFileName) == 0)
	{
		ComPtr<ID3DBlob> Blob;
		ComPtr<ID3DBlob> Error;
		INT flag = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY | D3D10_SHADER_PACK_MATRIX_ROW_MAJOR;

		HRESULT Result = ::D3DCompileFromFile(InFileName.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, NULL, "fx_5_0", flag, NULL, Blob.GetAddressOf(), Error.GetAddressOf());
		if (FAILED(Result))
		{
			if (Error != NULL)
			{
				string Str = (const char*)Error->GetBufferPointer();
				MessageBoxA(NULL, Str.c_str(), "Shader Error", MB_OK);
			}
			assert(false);
		}

		ComPtr<ID3DX11Effect> Effect;
		Result = ::D3DX11CreateEffectFromMemory(Blob->GetBufferPointer(), Blob->GetBufferSize(), 0, DEVICE.Get(), Effect.GetAddressOf());
		CHECK(Result);
		
		Shaders[InFileName] = FShaderDesc{Blob, Effect};
	}
	
	FShaderDesc Desc = Shaders.at(InFileName);
	ComPtr<ID3DX11Effect> Effect;
	Desc.Effect->CloneEffect(D3DX11_EFFECT_CLONE_FORCE_NONSINGLE, Effect.GetAddressOf());

	return FShaderDesc{Desc.Blob, Effect};
}
