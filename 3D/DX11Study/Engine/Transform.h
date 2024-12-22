#pragma once

#include "Component.h"

class FTransform : public FComponent
{
	using Super = FComponent;
public:
	FTransform();
	~FTransform();

	virtual void Awake() override;
	virtual void Update() override;

	void UpdateTransform();

	// Local
	FVector3 GetLocalScale() { return LocalScale; }
	void SetLocalScale(const FVector3& localScale) { LocalScale = localScale; UpdateTransform(); }
	FVector3 GetLocalRotation() { return LocalRotation; }
	void SetLocalRotation(const FVector3& localRotation) { LocalRotation = localRotation; UpdateTransform(); }
	FVector3 GetLocalPosition() { return LocalPosition; }
	void SetLocalPosition(const FVector3& localPosition) { LocalPosition = localPosition; UpdateTransform(); }

	// World
	FVector3 GetScale() { return Scale; }
	void SetScale(const FVector3& scale);
	FVector3 GetRotation() { return Rotation; }
	void SetRotation(const FVector3& rotation);
	FVector3 GetPosition() { return Position; }
	void SetPosition(const FVector3& position);

	FVector3 GetRight() { return World.Right(); }
	FVector3 GetUp() { return World.Up(); }
	FVector3 GetLook() { return World.Backward(); }

	FMatrix GetWorldMatrix() { return World; }

	// °èÃþ °ü°è
	bool HasParent() { return Parent != nullptr; }

	std::shared_ptr<FTransform> GetParent() { return Parent; }
	void SetParent(std::shared_ptr<FTransform> InParent) { Parent = InParent; }

	const std::vector<std::shared_ptr<FTransform>>& GetChildren() { return Children; }
	void AddChild(std::shared_ptr<FTransform> InChild) { Children.push_back(InChild); }

private:
	FVector3 LocalScale = { 1.f, 1.f, 1.f };
	FVector3 LocalRotation = { 0.f, 0.f, 0.f };
	FVector3 LocalPosition = { 0.f, 0.f, 0.f };

	// Cache
	FMatrix Local = FMatrix::Identity;
	FMatrix World = FMatrix::Identity;

	FVector3 Scale;
	FVector3 Rotation;
	FVector3 Position;

private:
	std::shared_ptr<FTransform> Parent;
	std::vector<std::shared_ptr<FTransform>> Children;
};

