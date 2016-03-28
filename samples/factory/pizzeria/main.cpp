#include <memory>
#include <string>
#include <stdexcept>

using namespace std;

class CDuck
{
public:
	virtual ~CDuck() = default;
};

class CMallarDuck : public CDuck
{
};

class CDecoyDuck : public CDuck {};

class CRubberDuck : public CDuck {};

void PlayWithDucks()
{
	bool hunting = true;
	bool picnic = true;
	bool inBathTube = true;

	unique_ptr<CDuck> duck;
	if (picnic)
	{
		duck = make_unique<CMallarDuck>();
	}
	else if (hunting)
	{
		duck = make_unique<CDecoyDuck>();
	}
	else if (inBathTube)
	{
		duck = make_unique<CRubberDuck>();
	}
}

class CPizza
{
public:
	virtual ~CPizza() = default;
	virtual void Prepare()
	{

	}
	virtual void Bake()
	{

	}
	void Cut()
	{

	}
	void Box()
	{

	}
};

class CCheezePizza : public CPizza
{
};

class CPepperoniPizza : public CPizza
{
};

class CNapolitanaPizza : public CPizza
{
};

class CSimplePizzaFactory
{
public:
	unique_ptr<CPizza> CreatePizza(const string& type) const
	{
		unique_ptr<CPizza> pizza;

		if (type == "cheeze")
		{
			pizza = make_unique<CCheezePizza>();
		}
		else if (type == "pepperoni")
		{
			pizza = make_unique<CPepperoniPizza>();
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

unique_ptr<CPizza> OrderPizza(const string& type)
{
	unique_ptr<CPizza> pizza;

	if (type == "cheeze")
	{
		pizza = make_unique<CCheezePizza>();
	}
	else if (type == "pepperoni")
	{
		pizza = make_unique<CPepperoniPizza>();
	}
	else if (type == "napolitana")
	{
		pizza = make_unique<CNapolitanaPizza>();
	}
	else
	{
		throw invalid_argument("Unknown pizza type");
	}

	pizza->Prepare();
	pizza->Bake();
	pizza->Cut();
	pizza->Box();

	return pizza;
}


int main()
{

	return 0;
}
