#pragma once

#include <set>
#include <functional>

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
protected:
	~IObserver() = default;
};

template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

template <class T>
class CObservable : public IObservable<T>
{
public:
	void RegisterObserver(IObserver<T> & observer) override
	{
		m_observers.insert(&observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		for (auto & observer : m_observers)
		{
			observer->Update(data);
		}
	}

	void RemoveObserver(IObserver<T> & observer) override
	{
		m_observers.erase(&observer);
	}

protected:
	virtual T GetChangedData()const = 0;

private:
	std::set<IObserver<T> *> m_observers;
};
