#pragma once
#include <functional>

// Generalised template declaration
template<typename T>
class Delegate;

// Specialised template definition
template<typename Ret, typename... Args>
class Delegate<Ret(Args...)>
{
private:
	// The function this delegate is storing and calling, initialized as nullptr to ensure isBound returns false initally
	std::function<Ret(Args...)> m_func = nullptr;

public:
	template<typename Owner>
	// Bind for setting m_func as a member function
	// in_owner		A pointer to the instance of the class that owns the given method (in_method)
	// in_method	A pointer to the method you wish to set m_func too
	void bind(Owner* in_owner, Ret(Owner::* in_method)(Args...))
	{
		// Early return and force unbind if the given owner is invalid
		if (in_owner == nullptr)
		{
			unbind();
			return;
		}

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
	// in_method	A pointer to the const method you wish to set m_func too
	void bind(const Owner* in_owner, Ret(Owner::* in_method)(Args...) const)
	{
		// Early return and force unbind if the given owner is invalid
		if (in_owner == nullptr)
		{
			unbind();
			return;
		}

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
		// Return the default constructed Ret if the bound function is invalid
		if (!isBound())
		{
			// If the return type is not void then return the default constructed value of Ret
			if constexpr (!std::is_void_v<Ret>) return Ret{};

			// If the return type is void then just early return from broadcast
			return;
		}

		// Execute the bound function
		return m_func(std::forward<Args>(in_args)...);
	}
};





// Generalised template declaration
template<typename T>
class MulticastDelegate;

// Specialised template definition
template<typename... Args>
class MulticastDelegate<void(Args...)>
{
private:
	// A struct to link the owning instance to the function for future removal logic
	struct OwnerFunctionPair
	{
		// void* is used because the array of this struct cannot be tempalted
		void* owner = nullptr;
		std::function<void(Args...)> func;

		OwnerFunctionPair(void* in_owner, std::function<void(Args...)> in_func)
		{
			owner = in_owner;
			func = in_func;
		}
	};

	// The array of owner-function pairs this delegate is storing and calling
	std::vector<OwnerFunctionPair> m_functions;

	// Clear all the bound functions related to a specific object from the m_functions vector
	void unbindAllFromOwner(void* in_owner)
	{
		// Early return if there are no bound functions or the passed object is invalid
		if (m_functions.empty() || in_owner == nullptr) return;

		// Use the stl remove_if to pass a lambda to erase so we can remove the pairs in-place
		m_functions.erase(std::remove_if(m_functions.begin(), m_functions.end(),
			[in_owner](const OwnerFunctionPair& pair) {
				return pair.owner == in_owner;
			}),
			m_functions.end()
		);
	}

public:
	template<typename Owner>
	// Add a method to the vector of stored functions
	// in_owner		A pointer to the instance of the class that owns the given method (in_method)
	// in_method	A reference to the method you wish to set m_func too
	void add(Owner* in_owner, void(Owner::* in_method)(Args...))
	{
		// Early return if in invalid object was passed
		if (in_owner == nullptr) return;

		// Lambda that returns owner->method(args);
		std::function<void(Args...)> func = [in_owner, in_method](Args... args) {
				// (in_owner->*in_method) represents in_owner->method
				// std::forward is used to retain the lvalue and rvalue states of the given arguments when passing it into the function
				return (in_owner->*in_method)(std::forward<Args>(args)...);
			};

		m_functions.push_back(OwnerFunctionPair(static_cast<void*>(in_owner), std::move(func)));
	}

	template<typename Owner>
	// Add a const method to the vector of stored functions
	// in_owner		A const pointer to the instance of the class that owns the given method (in_method)
	// in_method	A reference to the const method you wish to set m_func too
	void add(const Owner* in_owner, void(Owner::* in_method)(Args...) const)
	{
		// Early return if in invalid object was passed
		if (in_owner == nullptr) return;

		// Lambda that returns owner->method(args);
		std::function<void(Args...)> func = [in_owner, in_method](Args... args) {
				// (in_owner->*in_method) represents in_owner->method
				// std::forward is used to retain the lvalue and rvalue states of the given arguments when passing it into the function
				return (in_owner->*in_method)(std::forward<Args>(args)...);
			};

		m_functions.push_back(OwnerFunctionPair(static_cast<void*>(in_owner), std::move(func)));
	}

	// QoL publically exposed function so the user doesn't have to cast the object to void*
	template<typename Owner>
	void unbindAllFromOwner(Owner* in_owner)
	{
		unbindAllFromOwner(static_cast<void*>(in_owner));
	}

	// Calls m_func if it's bound
	void broadcast(Args... in_args) const
	{
		// Early return if there are no bound functions
		if (m_functions.empty()) return;

		for (const OwnerFunctionPair& pair : m_functions)
		{
			// Execute the function
			// std::forward is used to retain the lvalue and rvalue states of the given arguments when passing it into the function
			pair.func(std::forward<Args>(in_args)...);
		}
	}
};