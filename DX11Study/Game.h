#pragma once

#include "Geometry.h"

class FGame
{
public:
	FGame();
	virtual ~FGame();

	void Init(HWND InWindowHandle);
	void Update();
	void Render();

private:
	std::shared_ptr<class FGraphics> Graphics;
	std::shared_ptr<class FPipeline> Pipeline;
	std::shared_ptr<class UGameObject> GameObject;
};

