#pragma once

#include "IExecute.h"
#include "Geometry.h"

class FNormalDemo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	std::shared_ptr<class FShader> Shader;

	std::shared_ptr<class FGeometry<FVertexColorData>> Geometry;
	std::shared_ptr<class FVertexBuffer> VertexBuffer;
	std::shared_ptr<class FIndexBuffer> IndexBuffer;
	FMatrix World = FMatrix::Identity;

	std::shared_ptr<class FGameObject> Camera;

	std::shared_ptr<class FTexture> Texture;

	FVector3 LightDirection = FVector3(0.0f, -1.0f, 0.0f);
};

