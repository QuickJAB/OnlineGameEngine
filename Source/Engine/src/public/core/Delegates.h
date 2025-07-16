#pragma once

#include <functional>

template<typename T>
class Delegate;

template<typename Ret, typename... Args>
class Delegate<Ret(Args...)>
{
public:
protected:
private:
	std::function<Ret(Args...)> m_pFunc = nullptr;

public:
	template<typename Owner>
	void bind(Owner* i_pOwner, Ret(Owner::* i_pMethod)(Args...))
	{
		if (i_pOwner == nullptr)
		{
			unbind();
			return;
		}

		m_pFunc = [i_pOwner, i_pMethod](Args... args)->Ret
			{
				return (i_pOwner->*i_pMethod)(std::forward<Args>(args)...);
			};
	}

	template<typename Owner>
	void bind(const Owner* i_pOwner, Ret(Owner::* i_pMethod)(Args...) const)
	{
		if (i_pOwner == nullptr)
		{
			unbind();
			return;
		}

		m_func = [i_pOwner, i_pMethod](Args... args)->Ret
			{
				return (i_pOwner->*i_pMethod)(std::forward<Args>(args)...);
			};
	}
	
	void unbind() { m_pFunc = nullptr; }
	
	bool isBound() const { return static_cast<bool>(m_pFunc); }

	Ret broadcast(Args... i_Args) const
	{
		if (!isBound())
		{
			return Ret{};
		}

		return m_pFunc(std::forward<Args>(i_Args)...);
	}

protected:
private:
};

template<typename T>
class MulticastDelegate;

template<typename... Args>
class MulticastDelegate<void(Args...)>
{
public:
protected:
private:
	struct OwnerFunctionPair
	{
		void* pOwner = nullptr;
		std::function<void(Args...)> pFunc;

		OwnerFunctionPair(void* i_pOwner, std::function<void(Args...)> i_pFunc)
		{
			pOwner = i_pOwner;
			pFunc = i_pFunc;
		}
	};

	std::vector<OwnerFunctionPair> m_vFunctions;

public:
	template<typename Owner>
	void add(Owner* i_pOwner, void(Owner::* i_pMethod)(Args...))
	{
		if (i_pOwner == nullptr) return;

		std::function<void(Args...)> pFunc = [i_pOwner, i_pMethod](Args... args) {
				return (i_pOwner->*i_pMethod)(std::forward<Args>(args)...);
			};

		m_vFunctions.push_back(OwnerFunctionPair(static_cast<void*>(i_pOwner), std::move(pFunc)));
	}

	template<typename Owner>
	void add(const Owner* i_pOwner, void(Owner::* i_pMethod)(Args...) const)
	{
		if (i_pOwner == nullptr) return;

		std::function<void(Args...)> pFunc = [i_pOwner, in_method](Args... args) {
				return (i_pOwner->*in_method)(std::forward<Args>(args)...);
			};

		m_vFunctions.push_back(OwnerFunctionPair(static_cast<void*>(i_pOwner), std::move(pFunc)));
	}

	template<typename Owner>
	void unbindAllFromOwner(Owner* i_pOwner)
	{
		unbindAllFromOwner(static_cast<void*>(i_pOwner));
	}

	void broadcast(Args... i_Args) const
	{
		if (m_vFunctions.empty()) return;

		for (const OwnerFunctionPair& crPair : m_vFunctions)
		{
			crPair.func(std::forward<Args>(i_Args)...);
		}
	}

protected:
private:
	void unbindAllFromOwner(void* i_pOwner)
	{
		if (m_vFunctions.empty() || i_pOwner == nullptr) return;

		m_vFunctions.erase(std::remove_if(m_vFunctions.begin(), m_vFunctions.end(),
			[i_pOwner](const OwnerFunctionPair& crPair) {
				return crPair.pOwner == i_pOwner;
			}),
			m_vFunctions.end()
		);
	}
};