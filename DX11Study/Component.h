#pragma once

class FComponent
{
public:
	FComponent();
	virtual ~FComponent();

	virtual void Init() = 0;
	virtual void Update() = 0;

	std::shared_ptr<class FGameObject> GetGameObject() { return GameObject.lock(); }

private:
	std::weak_ptr<class FGameObject> GameObject;
};
