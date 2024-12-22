#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "MonoBehavior.h"
#include "Transform.h"
#include "Camera.h"
#include "MeshRenderer.h"

FGameObject::FGameObject()
{
}

FGameObject::~FGameObject()
{
}

void FGameObject::Awake()
{
	for (std::shared_ptr<FComponent> Component : Components)
	{
		if (Component != nullptr)
		{
			Component->Awake();
		}
	}
}

void FGameObject::Start()
{
	for (std::shared_ptr<FComponent> Component : Components)
	{
		if (Component != nullptr)
		{
			Component->Start();
		}
	}
}

void FGameObject::Update()
{
	for (std::shared_ptr<FComponent> Component : Components)
	{
		if (Component != nullptr)
		{
			Component->Update();
		}
	}

	for (std::shared_ptr<FMonoBehavior> Script : Scripts)
	{
		if (Script != nullptr)
		{
			Script->Update();
		}
	}
}

void FGameObject::LateUpdate()
{
	for (std::shared_ptr<FComponent> Component : Components)
	{
		if (Component != nullptr)
		{
			Component->LateUpdate();
		}
	}

	for (std::shared_ptr<FMonoBehavior> Script : Scripts)
	{
		if (Script != nullptr)
		{
			Script->LateUpdate();
		}
	}

}

void FGameObject::FixedUpdate()
{
	for (std::shared_ptr<FComponent> Component : Components)
	{
		if (Component != nullptr)
		{
			Component->FixedUpdate();
		}
	}

	for (std::shared_ptr<FMonoBehavior> Script : Scripts)
	{
		if (Script != nullptr)
		{
			Script->FixedUpdate();
		}
	}
}

std::shared_ptr<class FComponent> FGameObject::GetFixedComponent(EComponentType InType) const
{
	uint8 Index = static_cast<uint8>(InType);
	assert(Index < FIXED_COMPONENT_COUNT);
	return Components[Index];
}

std::shared_ptr<class FTransform> FGameObject::GetTransform() const
{
	std::shared_ptr<FComponent> Component = GetFixedComponent(EComponentType::Transform);
	return static_pointer_cast<FTransform>(Component);
}

std::shared_ptr<class FCamera> FGameObject::GetCamera() const
{
	std::shared_ptr<FComponent> Component = GetFixedComponent(EComponentType::Transform);
	return static_pointer_cast<FCamera>(Component);
}

std::shared_ptr<class FMeshRenderer> FGameObject::GetMeshRenderer() const
{
	std::shared_ptr<FComponent> Component = GetFixedComponent(EComponentType::Transform);
	return static_pointer_cast<FMeshRenderer>(Component);
}

std::shared_ptr<class FTransform> FGameObject::GetOrAddTransform()
{
	if (GetTransform() == nullptr)
	{
		std::shared_ptr<FTransform> Transform = std::make_shared<FTransform>();
		AddComponent(Transform);
	}

	return GetTransform();
}

void FGameObject::AddComponent(std::shared_ptr<FComponent> InComponent)
{
	InComponent->SetGameObject(shared_from_this());

	uint8 Index = static_cast<uint8>(InComponent->GetType());
	if (Index < FIXED_COMPONENT_COUNT)
	{
		Components[Index] = InComponent;
	}
	else
	{
		Scripts.push_back(dynamic_pointer_cast<FMonoBehavior>(InComponent));
	}
}
