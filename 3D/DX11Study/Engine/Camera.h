#pragma once

#include "Component.h"

enum class EProjectionType
{
	Perspective,
	Orthographic,
};

class FCamera : public FComponent
{
	using Super = FComponent;

public:
	FCamera();
	virtual ~FCamera();

	virtual void Update() override;

	void UpdateMatrix();

	void SetNear(float InNear) { Near = InNear; }
	void SetFar(float InFar) { Far = InFar; }
	void SetFov(float InFov) { Fov = InFov; }
	void SetWidth(float InWidth) { Width = InWidth; }
	void SetHeight(float InHeight) { Height = InHeight; }

	FMatrix& GetView() { return View; }
	FMatrix& GetProjection() { return Projection; }

private:
	FMatrix View = FMatrix::Identity;
	FMatrix Projection = FMatrix::Identity;

	float Near;
	float Far;
	float Fov;
	float Width;
	float Height;

public:
	static FMatrix S_View;
	static FMatrix S_Projection;
};
