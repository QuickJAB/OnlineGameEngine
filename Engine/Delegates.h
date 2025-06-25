#pragma once
#include <functional>

// Generlised template declaration
template<typename T>
class Delegate;

// Specialised template definition
template<typename Ret, typename... Args>
class Delegate<Ret(Args...)>
{
private:
	// The function this template is storing and calling, initalized as nullptr to ensure isBound returns false initally
	std::function<Ret(Args...)> m_func = nullptr;

public:
	template<typename Owner>
	// Bind for setting m_func as a member function
	// in_owner		A pointer to the instance of the class that owns the given method (in_method)
	// in_method	A reference to the method you wish to set m_func too
	void bind(Owner* in_owner, Ret(Owner::* in_method)(Args...))
	{
		// Lambda that returns owner->method(args);
		m_func = [in_owner, in_method](Args... args)->Ret {
			// (in_owner->*in_method) represents in_owner->method
			// std::forward is used to retain the lvalue and rvalue states of the given arguments when passing it into the function
				return (in_owner->*in_method)(std::forward<Args>(args)...);
			};
	}

	template<typename Owner>
	// Bind for setting m_func as a const member function
	// in_owner		A const pointer to the instance of the class that owns the given method (in_method)
	// in_method	A reference to the const method you wish to set m_func too
	void bind(const Owner* in_owner, Ret(Owner::* in_method)(Args...) const)
	{
		// Lambda that returns owner->method(args);
		m_func = [in_owner, in_method](Args... args)->Ret {
			// (in_owner->*in_method) represents in_owner->method
			// std::forward is used to retain the lvalue and rvalue states of the given arguments when passing it into the function
				return (in_owner->*in_method)(std::forward<Args>(args)...);
			};
	}
	
	// Reset m_func to a nullptr
	void unbind() { m_func = nullptr; }
	
	// Check if m_func exists
	bool isBound() const { return static_cast<bool>(m_func); }

	// Calls m_func if it's bound
	Ret broadcast(Args... in_args) const
	{
		// Check if Ret is void
		if constexpr(std::is_void_v<Ret>)
		{
			// (in_owner->*in_method) represents in_owner->method
			// std::forward is used to retain the lvalue and rvalue states of the given arguments when passing it into the function
			if (isBound()) m_func(std::forward<Args>(in_args)...);
		}
		else
		{
			// If Ret is a non-void type then attempt to call m_func if it's bound, otherwise return a default constructed value of Ret
			// std::forward is used to retain the lvalue and rvalue states of the given arguments when passing it into the function
			return isBound() ? m_func(std::forward<Args>(in_args)...) : Ret{};
		}
	}
};