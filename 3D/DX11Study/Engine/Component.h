#pragma once

enum class EComponentType : uint8
{
	Transform,
	MeshRenderer,
	Camera,
	Animator,
	// ...
	Script,
	End,
};

enum
{
	FIXED_COMPONENT_COUNT = static_cast<uint8>(EComponentType::End) - 1
};

class FComponent
{
public:
	FComponent(EComponentType InType);
	virtual ~FComponent();

	virtual void Awake() { }
	virtual void Start() { }
	virtual void Update() { }
	virtual void LateUpdate() { }
	virtual void FixedUpdate() { }

public:
	EComponentType GetType() const { return Type; }

	std::shared_ptr<class FGameObject> GetGameObject() const;
	std::shared_ptr<class FTransform> GetTransform() const;

private:
	friend class FGameObject;
	void SetGameObject(std::shared_ptr<FGameObject> InGameObject) { GameObject = InGameObject; }

protected:
	EComponentType Type;
	std::weak_ptr<FGameObject> GameObject;
};
