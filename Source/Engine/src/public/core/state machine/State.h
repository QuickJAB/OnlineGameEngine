#pragma once

#include <string>

class State
{
public:
protected:
private:

public:
	State() = default;
	~State() = default;

	virtual void enter();
	virtual std::string update(const float i_cfDt);
	virtual void exit();

protected:
private:
};