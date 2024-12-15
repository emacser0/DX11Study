#include "pch.h"
#include "Technique.h"

void FTechnique::Draw(UINT InPass, UINT vertexCount, UINT startVertexLocation)
{
	Passes[InPass].Draw(vertexCount, startVertexLocation);
}

void FTechnique::DrawIndexed(UINT InPass, UINT InIndexCount, UINT startIndexLocation, INT baseVertexLocation)
{
	Passes[InPass].DrawIndexed(InIndexCount, startIndexLocation, baseVertexLocation);
}

void FTechnique::DrawInstanced(UINT InPass, UINT vertexCountPerInstance, UINT InInstanceCount, UINT startVertexLocation, UINT startInstanceLocation)
{
	Passes[InPass].DrawInstanced(vertexCountPerInstance, InInstanceCount, startVertexLocation, startInstanceLocation);
}

void FTechnique::DrawIndexedInstanced(UINT InPass, UINT InIndexCountPerInstance, UINT InInstanceCount, UINT startIndexLocation, INT baseVertexLocation, UINT startInstanceLocation)
{
	Passes[InPass].DrawIndexedInstanced(InIndexCountPerInstance, InInstanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation);
}

void FTechnique::Dispatch(UINT InPass, UINT InX, UINT InY, UINT InZ)
{
	Passes[InPass].Dispatch(InX, InY, InZ);
}