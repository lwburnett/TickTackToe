#pragma once
#include "GameTime.h"


class IUpdateable
{
public:
	virtual ~IUpdateable() = default;
	virtual void Update(const GameTime& iGameTime) = 0;
};
