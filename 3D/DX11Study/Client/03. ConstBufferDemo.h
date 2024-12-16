#pragma once

#include "IExecute.h"

#include "Geometry.h"

class FConstBufferDemo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	std::shared_ptr<FShader> Shader;
	std::shared_ptr<FGeometry<FVertexColorData>> Geometry;
	std::shared_ptr<FVertexBuffer> VertexBuffer;
	std::shared_ptr<FIndexBuffer> IndexBuffer;

	FVector3 Translation = FVector3(0.0f, 0.0f, 0.0f);

	FMatrix World = FMatrix::Identity;
	FMatrix View = FMatrix::Identity;
	FMatrix Projection = FMatrix::Identity;
};
