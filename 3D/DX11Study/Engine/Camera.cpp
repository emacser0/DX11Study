#include "pch.h"
#include "Camera.h"
#include "Transform.h"

FMatrix FCamera::S_View = FMatrix::Identity;
FMatrix FCamera::S_Projection = FMatrix::Identity;

FCamera::FCamera()
	: Super(EComponentType::Camera)
	, Near(1.0f)
	, Far(1000.0f)
	, Fov(XM_PI / 4.0f)
	, Width(0.0f)
	, Height(0.0f)
{
	Width = static_cast<float>(GAME->GetGameDesc().Width);
	Height = static_cast<float>(GAME->GetGameDesc().Height);
}

FCamera::~FCamera()
{
}

void FCamera::Update()
{
	UpdateMatrix();
}

void FCamera::UpdateMatrix()
{
	FVector3 EyePosition = GetTransform()->GetPosition();
	FVector3 FocusPosition = EyePosition * GetTransform()->GetLook();
	FVector3 UpDirection = GetTransform()->GetUp();
	S_View = ::XMMatrixLookAtLH(EyePosition, FocusPosition, UpDirection);

	S_Projection = ::XMMatrixPerspectiveFovLH(Fov, Width / Height, Near, Far);
}
