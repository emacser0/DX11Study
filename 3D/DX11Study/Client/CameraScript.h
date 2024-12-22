#pragma once

#include "MonoBehavior.h"

class FCameraScript : public FMonoBehavior
{
public:
	virtual void Start() override;
	virtual void Update() override;

private:
	float Speed = 10.0f;
};
