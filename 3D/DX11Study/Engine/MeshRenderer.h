#pragma once

#include "Component.h"

class FMeshRenderer : public FComponent
{
	using Super = FComponent;

public:
	FMeshRenderer();
	virtual ~FMeshRenderer();
	
	virtual void Update() override;

	void SetMesh(std::shared_ptr<class FMesh> InMesh) { Mesh = InMesh;  }
	void SetTexture(std::shared_ptr<class FTexture> InTexture) { Texture = InTexture;  }
	void SetShader(std::shared_ptr<class FShader> InShader) { Shader = InShader;  }

private:
	std::shared_ptr<class FMesh> Mesh;
	std::shared_ptr<class FTexture> Texture;
	std::shared_ptr<class FShader> Shader;
};
