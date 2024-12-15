#pragma once
#include "Pass.h"

struct FTechnique
{
	std::wstring Name;
	D3DX11_TECHNIQUE_DESC Desc;
	ComPtr<ID3DX11EffectTechnique> Technique;
	std::vector<FPass> Passes;

	void Draw(UINT InPass, UINT vertexCount, UINT startVertexLocation = 0);
	void DrawIndexed(UINT InPass, UINT InIndexCount, UINT InStartIndexLocation = 0, INT InBaseVertexLocation = 0);
	void DrawInstanced(UINT InPass, UINT vertexCountPerInstance, UINT InInstanceCount, UINT InStartVertexLocation = 0, UINT InStartInstanceLocation = 0);
	void DrawIndexedInstanced(UINT InPass, UINT InIndexCountPerInstance, UINT InInstanceCount, UINT InStartIndexLocation = 0, INT InBaseVertexLocation = 0, UINT startInstanceLocation = 0);

	void Dispatch(UINT InPass, UINT InX, UINT InY, UINT InZ);
};
