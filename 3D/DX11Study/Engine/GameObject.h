#pragma once

#include "Component.h"

class FGameObject : public std::enable_shared_from_this<FGameObject>
{
public:
	FGameObject();
	virtual ~FGameObject();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();

	std::shared_ptr<class FComponent> GetFixedComponent(EComponentType InType) const;
	std::shared_ptr<class FTransform> GetTransform() const;
	std::shared_ptr<class FCamera> GetCamera() const;
	std::shared_ptr<class FMeshRenderer> GetMeshRenderer() const;

	std::shared_ptr<class FTransform> GetOrAddTransform();

	void AddComponent(std::shared_ptr<class FComponent> InComponent);

protected:
	std::array<std::shared_ptr<class FComponent>, FIXED_COMPONENT_COUNT> Components;
	std::vector<std::shared_ptr<class FMonoBehavior>> Scripts;
};
