#include "pch.h"
#include "CameraScript.h"
#include "Transform.h"

void FCameraScript::Start()
{
}

void FCameraScript::Update()
{
	float DeltaTime = TIME->GetDeltaTime();

	std::shared_ptr<FTransform> Transform = GetTransform();

	FVector3 Position = Transform->GetPosition();

	if (INPUT->GetButton(EKeyType::W))
	{
		Position += Transform->GetLook() * Speed * DeltaTime;
	}

	if (INPUT->GetButton(EKeyType::S))
	{
		Position += Transform->GetLook() * Speed * DeltaTime;
	}

	if (INPUT->GetButton(EKeyType::A))
	{
		Position += Transform->GetLook() * Speed * DeltaTime;
	}

	if (INPUT->GetButton(EKeyType::D))
	{
		Position += Transform->GetLook() * Speed * DeltaTime;
	}

	Transform->SetPosition(Position);

	if (INPUT->GetButton(EKeyType::Q))
	{
		FVector3 Rotation = Transform->GetLocalRotation();
		Rotation.x += DeltaTime * 0.5f;
		Transform->SetLocalRotation(Rotation);
	}

	if (INPUT->GetButton(EKeyType::E))
	{
		FVector3 Rotation = Transform->GetLocalRotation();
		Rotation.x -= DeltaTime * 0.5f;
		Transform->SetLocalRotation(Rotation);
	}

	if (INPUT->GetButton(EKeyType::Z))
	{
		FVector3 Rotation = Transform->GetLocalRotation();
		Rotation.y += DeltaTime * 0.5f;
		Transform->SetLocalRotation(Rotation);
	}

	if (INPUT->GetButton(EKeyType::C))
	{
		FVector3 Rotation = Transform->GetLocalRotation();
		Rotation.y -= DeltaTime * 0.5f;
		Transform->SetLocalRotation(Rotation);
	}
}
