#include "pch.h"
#include "Transform.h"

FTransform::FTransform()
	: Local(FMatrix::Identity)
	, World(FMatrix::Identity)
{
}

FTransform::~FTransform()
{
}

void FTransform::Init()
{
}

void FTransform::Update()
{
}

FVector3 EulerToAngles(const FQuat& InQuat)
{
	FVector3 Angles;

	// roll (x-axis rotation)
	double SinRCosP = 2 * (InQuat.w * InQuat.x * InQuat.y * InQuat.z);
	double CosRCosP = 1 - 2 * (InQuat.x * InQuat.x + InQuat.y * InQuat.y);
	Angles.x = std::atan2(SinRCosP, CosRCosP);

	// pitch (y-axis rotation)
	double SinP = std::sqrt(1 + 2 * (InQuat.w * InQuat.y - InQuat.x * InQuat.z));
	double CosP = std::sqrt(1 - 2 * (InQuat.w * InQuat.y - InQuat.x * InQuat.z));
	Angles.y = 2 * std::atan2(SinP, CosP) - 3.14159f / 2.0f;

	// yaw (z-axis rotation)
	double SinYCosP = 2 * (InQuat.w * InQuat.z + InQuat.x * InQuat.y);
	double CosYCosP = 1 - 2 * (InQuat.y * InQuat.y + InQuat.z * InQuat.z);
	Angles.z = std::atan2(SinYCosP, CosYCosP);

	return Angles;
}

void FTransform::UpdateTransform()
{
	FMatrix TranslationMatrix = FMatrix::CreateTranslation(LocalPosition);
	FMatrix RotationMatrix = FMatrix::CreateRotationX(LocalRotation.x);
	RotationMatrix *= FMatrix::CreateRotationY(LocalRotation.y);
	RotationMatrix *= FMatrix::CreateRotationZ(LocalRotation.z);
	FMatrix ScaleMatrix = FMatrix::CreateScale(LocalScale);

	Local = ScaleMatrix * RotationMatrix * TranslationMatrix;

	if (HasParent())
	{
		World = Local * Parent->GetWorldMatrix();
	}
	else
	{
		World = Local;
	}

	FQuat Quat;
	World.Decompose(Scale, Quat, Position);
	Rotation = EulerToAngles(Quat);

	Right = FVector3::TransformNormal(FVector3::Right, World);
	Up = FVector3::TransformNormal(FVector3::Up, World);
	Look = FVector3::TransformNormal(FVector3::Backward, World);

	for (const std::shared_ptr<FTransform>& Child : Children)
	{
		Child->UpdateTransform();
	}
}

void FTransform::SetPosition(const FVector3& InPosition)
{
	if (HasParent())
	{
		FMatrix WorldToParentLocalMatrix = Parent->GetWorldMatrix().Invert();

		FVector3 Position;
		Position.Transform(InPosition, WorldToParentLocalMatrix);

		SetLocalPosition(Position);
	}
	else
	{
		SetLocalPosition(InPosition);
	}
}

void FTransform::SetRotation(const FVector3& InRotation)
{
	if (HasParent())
	{
		FMatrix InverseMatrix = Parent->GetWorldMatrix().Invert();

		FVector3 Rotation;
		Rotation.TransformNormal(InRotation, InverseMatrix);

		SetLocalRotation(Rotation);
	}
	else
	{
		SetLocalRotation(InRotation);
	}
}

void FTransform::SetScale(const FVector3& InScale)
{
	if (HasParent())
	{
		FVector3 ParentScale = Parent->GetScale();
		FVector3 Scale = InScale;
		Scale.x /= ParentScale.x;
		Scale.y /= ParentScale.y;
		Scale.z /= ParentScale.z;
		SetLocalScale(Scale);

	}
	else
	{
		SetLocalScale(Scale);
	}
}
