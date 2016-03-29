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

	virtual unique_ptr<CPizza> OrderPizza(const string& type)
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

void MakeSomePizza(CPizzaStore & pizzaStore, const string& type)
{
	pizzaStore.OrderPizza(type);
	cout << "Thank you for visiting our pizza store\n";
}

int main()
{
	auto nyPizzaFactory = make_unique<CNYPizzaFactory>();
	CPizzaStore ps(move(nyPizzaFactory));
	MakeSomePizza(ps, "peperoni");

	return 0;
}
