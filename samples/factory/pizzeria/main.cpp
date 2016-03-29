#include <memory>
#include <string>
#include <stdexcept>

#include "Pizza.h"

using namespace std;

// Простая фабрика для создания пиццы
class CSimplePizzaFactory
{
public:
	virtual unique_ptr<CPizza> CreatePizza(const string& type) const
	{
		unique_ptr<CPizza> pizza;

		if (type == "cheeze")
		{
			pizza = make_unique<CCheezePizza>();
		}
		else if (type == "peperoni")
		{
			pizza = make_unique<CPeperoniPizza>();
		}
		else if (type == "napolitana")
		{
			pizza = make_unique<CNapolitanaPizza>();
		}
		else
		{
			throw invalid_argument("Unknown pizza type");
		}
		return pizza;
	}
};

// Пиццерия
class CPizzaStore
{
public:
	// Параметризуем пиццерию объектом фабрики
	CPizzaStore(unique_ptr<CSimplePizzaFactory> && factory)
		:m_factory(move(factory))
	{
	}

	unique_ptr<CPizza> OrderPizza(const string& type)
	{
		// Делегируем создание экземпляра пиццы фабрике
		auto pizza = m_factory->CreatePizza(type);

		pizza->Prepare();
		pizza->Bake();
		pizza->Cut();
		pizza->Box();

		return pizza;
	}
private:
	unique_ptr<CSimplePizzaFactory> m_factory;
};

class CNYPizzaFactory : public CSimplePizzaFactory
{
public:
	unique_ptr<CPizza> CreatePizza(const string& type) const override
	{
		unique_ptr<CPizza> pizza;

		if (type == "cheeze")
		{
			pizza = make_unique<CNYCheezePizza>();
		}
		else if (type == "peperoni")
		{
			pizza = make_unique<CNYPeperoniPizza>();
		}
		else if (type == "napolitana")
		{
			pizza = make_unique<CNYNapolitanaPizza>();
		}
		else
		{
			throw invalid_argument("Unknown pizza type");
		}
		return pizza;
	}
};

void OrderPizzaWithSimpleFactory()
{
	auto nyPizzaFactory = make_unique<CNYPizzaFactory>();
	CPizzaStore pizzaStore(move(nyPizzaFactory));
	auto pizza = pizzaStore.OrderPizza("peperoni");
}

class CAbstractPizzaStore
{
public:
	unique_ptr<CPizza> OrderPizza(const string& type)
	{
		// Делегируем создание экземпляра пиццы подклассам
		auto pizza = CreatePizza(type);

		// Дальнейшие шаги выполняем по строго заданному алгоритму
		pizza->Prepare();
		pizza->Bake();
		pizza->Cut();
		pizza->Box();

		return pizza;
	}
protected:
	// Конкретные подклассы обязаны реализовать данный метод
	virtual unique_ptr<CPizza> CreatePizza(const string& type) const = 0;
};

// Пиццерия, готовящая пиццу в нью-йоркском стиле
class CNYPizzaStore : public CAbstractPizzaStore
{
protected:
	// Все, что нужно - реализовать метод CreatePizza нужным образом
	unique_ptr<CPizza> CreatePizza(const string& type) const override
	{
		unique_ptr<CPizza> pizza;

		if (type == "cheeze")
		{
			pizza = make_unique<CNYCheezePizza>();
		}
		else if (type == "peperoni")
		{
			pizza = make_unique<CNYPeperoniPizza>();
		}
		else if (type == "napolitana")
		{
			pizza = make_unique<CNYNapolitanaPizza>();
		}
		else
		{
			throw invalid_argument("Unknown pizza type");
		}
		return pizza;
	}
};

void OrderPizzaWithFactoryMethod(CAbstractPizzaStore & pizzaStore)
{
	auto pizza = pizzaStore.OrderPizza("peperoni");
}

int main()
{
	OrderPizzaWithSimpleFactory();

	CNYPizzaStore pizzaStore;
	OrderPizzaWithFactoryMethod(pizzaStore);

	return 0;
}
