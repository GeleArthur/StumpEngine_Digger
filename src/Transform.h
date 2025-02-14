#pragma once

#include "Component.h"

class Transform final : public Component
{
public:
	explicit Transform(float x, float y); //TODO: Matrix support 

	// Can make these public to avoid getters and setters
	float x;
	float y;

private:
};

