#include "pch.h"
#include "Pass.h"

void FPass::Draw(UINT InVertexCount, UINT InStartVertexLocation)
{
	BeginDraw();
	{
		DC->Draw(InVertexCount, InStartVertexLocation);
	}
	EndDraw();
}

void FPass::DrawIndexed(UINT InIndexCount, UINT InStartIndexLocation, INT InBaseVertexLocation)
{
	BeginDraw();
	{
		DC->DrawIndexed(InIndexCount, InStartIndexLocation, InBaseVertexLocation);
	}
	EndDraw();
}

void FPass::DrawInstanced(UINT InVertexCountPerInstance, UINT InInstanceCount, UINT InStartVertexLocation, UINT InStartInstanceLocation)
{
	BeginDraw();
	{
		DC->DrawInstanced(InVertexCountPerInstance, InInstanceCount, InStartVertexLocation, InStartInstanceLocation);
	}
	EndDraw();
}

void FPass::DrawIndexedInstanced(UINT InIndexCountPerInstance, UINT InInstanceCount, UINT InStartIndexLocation, INT InBaseVertexLocation, UINT InStartInstanceLocation)
{
	BeginDraw();
	{
		DC->DrawIndexedInstanced(InIndexCountPerInstance, InInstanceCount, InStartIndexLocation, InBaseVertexLocation, InStartIndexLocation);
	}
	EndDraw();
}

void FPass::BeginDraw()
{
	Pass->ComputeStateBlockMask(&StateblockMask);

	DC->IASetInputLayout(InputLayout.Get());
	Pass->Apply(0, DC.Get());
}

void FPass::EndDraw()
{
	if (StateblockMask.RSRasterizerState == 1)
		DC->RSSetState(StateBlock->RSRasterizerState.Get());

	if (StateblockMask.OMDepthStencilState == 1)
		DC->OMSetDepthStencilState(StateBlock->OMDepthStencilState.Get(), StateBlock->OMStencilRef);

	if (StateblockMask.OMBlendState == 1)
		DC->OMSetBlendState(StateBlock->OMBlendState.Get(), StateBlock->OMBlendFactor, StateBlock->OMSampleMask);

	DC->HSSetShader(NULL, NULL, 0);
	DC->DSSetShader(NULL, NULL, 0);
	DC->GSSetShader(NULL, NULL, 0);
}

void FPass::Dispatch(UINT InX, UINT InY, UINT InZ)
{
	Pass->Apply(0, DC.Get());
	DC->Dispatch(InX, InY, InZ);

	ID3D11ShaderResourceView* null[1] = { 0 };
	DC->CSSetShaderResources(0, 1, null);

	ID3D11UnorderedAccessView* nullUav[1] = { 0 };
	DC->CSSetUnorderedAccessViews(0, 1, nullUav, NULL);

	DC->CSSetShader(NULL, NULL, 0);
}