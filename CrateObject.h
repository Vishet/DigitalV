#pragma once

#include "Object.h"

class CrateObject : public Object
{
public:
	CrateObject() = default;

	CrateObject(const CrateObject&) = delete;
	CrateObject(const CrateObject&&) = delete;
	CrateObject operator=(const CrateObject&) = delete;
	CrateObject operator=(const CrateObject&&) = delete;


	void Draw() override;
};

