#pragma once

#include "Component.h"

class FTransform : public FComponent
{
public:
	FTransform();
	virtual ~FTransform();

	virtual void Init() override;
	virtual void Update() override;

	void UpdateTransform();

	FVector3 GetLocalPosition() const { return LocalPosition; }
	FVector3 GetLocalRotation() const { return LocalRotation; }
	FVector3 GetLocalScale() const { return LocalScale; }

	void SetLocalPosition(const FVector3& InLocalPosition) { LocalPosition = InLocalPosition; UpdateTransform(); }
	void SetLocalRotation(const FVector3& InLocalRotation) { LocalRotation = InLocalRotation; UpdateTransform(); }
	void SetLocalScale(const FVector3& InLocalScale) { LocalScale = InLocalScale; UpdateTransform(); }

	FVector3 GetPosition() const { return Position; }
	FVector3 GetRotation() const { return Rotation; }
	FVector3 GetScale() const { return Scale; }

	void SetPosition(const FVector3& InPosition);
	void SetRotation(const FVector3& InRotation);
	void SetScale(const FVector3& InScale);

	FMatrix GetWorldMatrix() const { return World; }

	bool HasParent() const { return Parent != nullptr; }

	std::shared_ptr<FTransform> GetParent() const { return Parent; }
	void SetParent(std::shared_ptr<FTransform> InParent) { Parent = InParent; }

	const std::vector<std::shared_ptr<FTransform>>& GetChildren() const { return Children; }
	void AddChild(std::shared_ptr<FTransform> InChild) { Children.push_back(InChild); }

private:
	FVector3 LocalScale = { 1.f, 1.f, 1.f };
	FVector3 LocalRotation = { 0.f, 0.f, 0.f };
	FVector3 LocalPosition = { 0.f, 0.f, 0.f };

	FMatrix Local;
	FMatrix World;

	FVector3 Position;
	FVector3 Rotation;
	FVector3 Scale;

	FVector3 Right;
	FVector3 Up;
	FVector3 Look;

	std::shared_ptr<FTransform> Parent;
	std::vector<std::shared_ptr<FTransform>> Children;
};
