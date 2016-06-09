#pragma once

#include <memory>
#include <cassert>

template <typename T>
class CCow
{
	template <typename U>
	struct CCopyConstr
	{
		static std::unique_ptr<U> Copy(U const& other)
		{
			return std::make_unique<T>(other);
		}
	};

	template <typename U>
	struct CCloneConstr
	{
		static std::unique_ptr<U> Copy(U const& other)
		{
			return other.Clone();
		}
	};
	using CCopyClass = typename std::conditional<!std::is_abstract<T>::value && std::is_copy_constructible<T>::value, CCopyConstr<T>, CCloneConstr<T>>::type;

public:
	class CWriteProxy
	{
	public:
		T * operator->()
		{
			return m_p;
		}

	private:
		friend class CCow;
		CWriteProxy(CWriteProxy const&) = default;
		CWriteProxy& operator=(CWriteProxy const&) = default;

		CWriteProxy(T * p)
			:m_p(p)
		{
		}

		T * m_p;
	};

	template <typename ...Args, typename = std::enable_if<!std::is_abstract<T>::value>::type>
	CCow(Args&&... args)
		:m_shared(std::make_shared<T>(std::forward<Args>(args)...))
	{
	}

	// avoid duplicate object
	CCow(CCow<T> && rhs)
		:m_shared(std::move(rhs.m_shared))
	{
	}

	CCow(std::unique_ptr<T> pUniqueObj)
		:m_shared(std::move(pUniqueObj))
	{
	}

	CCow & operator=(CCow<T> && rhs)
	{
		m_shared = std::move(rhs.m_shared);
		return *this;
	}

	template <typename U>
	CCow(CCow<U> & rhs)
		:m_shared(rhs.m_shared)
	{
	}

	template <typename U>
	CCow & operator=(CCow<U> & rhs)
	{
		m_shared = rhs.m_shared;
		return *this;
	}

	// vc generate copy, but c++11 don't allow this, implement for gcc

	CCow(CCow const& rhs)
		:m_shared(rhs.m_shared)
	{
	}

	CCow & operator=(CCow const& rhs)
	{
		m_shared = rhs.m_shared;
		return *this;
	}

	T const& operator*()const
	{
		assert(m_shared);
		return *m_shared;
	}

	T const* operator->()const
	{
		assert(m_shared);
		return m_shared.get();
	}

	CWriteProxy operator--(int)
	{
		assert(m_shared);
		EnsureUnique();
		return CWriteProxy(m_shared.get());
	}

	T & Write()
	{
		assert(m_shared);
		EnsureUnique();
		return *m_shared;
	}

	std::shared_ptr<T> & WriteShared()
	{
		assert(m_shared);
		EnsureUnique();
		return m_shared;
	}

private:
	void EnsureUnique()
	{
		if (!m_shared.unique())
		{
			m_shared = CCopyClass::Copy(*m_shared);
		}
	}

private:
	std::shared_ptr<T> m_shared;
};
