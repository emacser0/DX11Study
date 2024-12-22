#include "pch.h"
#include "Component.h"
#include "GameObject.h"

FComponent::FComponent(EComponentType InType)
	: Type(InType)
{
}

FComponent::~FComponent()
{
}

std::shared_ptr<class FGameObject> FComponent::GetGameObject() const
{
	return GameObject.lock();
}

std::shared_ptr<class FTransform> FComponent::GetTransform() const
{
	return GameObject.lock()->GetTransform();
}
