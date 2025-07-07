#pragma once

#include <string>

class State
{
public:
	State() = default;
	~State() = default;

	virtual void enter();
	virtual std::string update(float in_dt);
	virtual void exit();
};