#pragma once

struct FStateBlock
{
	ComPtr<ID3D11RasterizerState> RSRasterizerState;
	ComPtr<ID3D11BlendState> OMBlendState;
	FLOAT OMBlendFactor[4];
	UINT OMSampleMask;
	ComPtr<ID3D11DepthStencilState> OMDepthStencilState;
	UINT OMStencilRef;
};

struct FPass
{
	std::wstring Name;
	ID3DX11EffectPass* Pass;
	D3DX11_PASS_DESC Desc;

	ComPtr<ID3D11InputLayout> InputLayout;
	D3DX11_PASS_SHADER_DESC PassVsDesc;
	D3DX11_EFFECT_SHADER_DESC EffectVsDesc;
	std::vector<D3D11_SIGNATURE_PARAMETER_DESC> signatureDescs;

	D3DX11_STATE_BLOCK_MASK StateblockMask;
	std::shared_ptr<FStateBlock> StateBlock;

	void Draw(UINT InVertexCount, UINT InStartVertexLocation = 0);
	void DrawIndexed(UINT InIndexCount, UINT InStartIndexLocation = 0, INT InBaseVertexLocation = 0);
	void DrawInstanced(UINT InVertexCountPerInstance, UINT InInstanceCount, UINT InStartVertexLocation = 0, UINT InStartInstanceLocation = 0);
	void DrawIndexedInstanced(UINT InIndexCountPerInstance, UINT InInstanceCount, UINT InStartIndexLocation = 0, INT InBaseVertexLocation = 0, UINT InStartInstanceLocation = 0);

	void BeginDraw();
	void EndDraw();

	void Dispatch(UINT InX, UINT InY, UINT InZ);
};
