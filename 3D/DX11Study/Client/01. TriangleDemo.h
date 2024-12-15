#pragma once

#include "IExecute.h"

class FTriangleDemo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	std::shared_ptr<FShader> Shader;
	std::vector<FVertexData> Vertices;
	std::shared_ptr<FVertexBuffer> Buffer;
};
