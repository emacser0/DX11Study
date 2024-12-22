#pragma once

#include "IExecute.h"
#include "Geometry.h"

class FMeshDemo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	std::shared_ptr<class FShader> Shader;

	std::shared_ptr<class FGameObject> Object;
	std::shared_ptr<class FGameObject> Camera;
};
