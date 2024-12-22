#pragma once

#include "Component.h"

class FMonoBehavior : public FComponent
{
	using Super = FComponent;
public:
	FMonoBehavior();
	virtual ~FMonoBehavior();
};
