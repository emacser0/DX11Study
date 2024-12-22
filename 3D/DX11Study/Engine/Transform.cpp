#include "pch.h"
#include "Transform.h"

FTransform::FTransform() : Super(EComponentType::Transform)
{

}

FTransform::~FTransform()
{

}

void FTransform::Awake()
{
}

void FTransform::Update()
{
}

FVector3 ToEulerAngles(FQuaternion q)
{
	FVector3 Angles;

	// roll (x-axis rotation)
	double SinRCosP = 2 * (q.w * q.x + q.y * q.z);
	double CosRCosP = 1 - 2 * (q.x * q.x + q.y * q.y);
	Angles.x = std::atan2(SinRCosP, CosRCosP);

	// pitch (y-axis rotation)
	double SinP = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
	double CosP = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
	Angles.y = 2 * std::atan2(SinP, CosP) - 3.14159f / 2;

	// yaw (z-axis rotation)
	double SinYCosP = 2 * (q.w * q.z + q.x * q.y);
	double CosYCosP = 1 - 2 * (q.y * q.y + q.z * q.z);
	Angles.z = std::atan2(SinYCosP, CosYCosP);

	return Angles;
}

void FTransform::UpdateTransform()
{
	FMatrix MatScale = FMatrix::CreateScale(LocalScale);
	FMatrix MatRotation = FMatrix::CreateRotationX(LocalRotation.x);
	MatRotation *= FMatrix::CreateRotationY(LocalRotation.y);
	MatRotation *= FMatrix::CreateRotationZ(LocalRotation.z);
	FMatrix MatTranslation = FMatrix::CreateTranslation(LocalPosition);

	Local = MatScale * MatRotation * MatTranslation;

	if (HasParent())
	{
		World = Local * Parent->GetWorldMatrix();
	}
	else
	{
		World = Local;
	}

	FQuaternion Quat;
	World.Decompose(Scale, Quat, Position);
	Rotation = ToEulerAngles(Quat);

	// Children
	for (const std::shared_ptr<FTransform>& Child : Children)
		Child->UpdateTransform();
}

void FTransform::SetScale(const FVector3& InWorldScale)
{
	if (HasParent())
	{
		FVector3 ParentScale = Parent->GetScale();
		FVector3 LocalScale = InWorldScale;
		LocalScale.x /= ParentScale.x;
		LocalScale.y /= ParentScale.y;
		LocalScale.z /= ParentScale.z;
		SetLocalScale(LocalScale);
	}
	else
	{
		SetLocalScale(InWorldScale);
	}
}

void FTransform::SetRotation(const FVector3& InWorldRotation)
{
	if (HasParent())
	{
		FMatrix InverseFMatrix = Parent->GetWorldMatrix().Invert();

		FVector3 LocalRotation;
		LocalRotation.TransformNormal(InWorldRotation, InverseFMatrix);

		SetLocalRotation(LocalRotation);
	}
	else
		SetLocalRotation(InWorldRotation);
}

void FTransform::SetPosition(const FVector3& InWorldPosition)
{
	if (HasParent())
	{
		FMatrix WorldToParentLocalFMatrix = Parent->GetWorldMatrix().Invert();

		FVector3 LocalPosition;
		LocalPosition.Transform(InWorldPosition, WorldToParentLocalFMatrix);

		SetLocalPosition(LocalPosition);
	}
	else
	{
		SetLocalPosition(InWorldPosition);
	}
}
