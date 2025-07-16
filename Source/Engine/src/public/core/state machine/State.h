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
	virtual std::string update(float i_fDt);
	virtual void exit();

protected:
private:
};