#pragma once
#include "Pizza.h"


class CPizzaStore
{
public:
	std::unique_ptr<CPizza> OrderPizza(const std::string& type)
	{
		auto pizza = CreatePizza(type);

		std::cout << "--- Making a " << pizza->GetName() + " ---" << std::endl;

		pizza->Prepare();
		pizza->Bake();
		pizza->Cut();
		pizza->Box();

		return pizza;
	}

	virtual ~CPizzaStore() = default;
protected:
	virtual std::unique_ptr<CPizza> CreatePizza(const std::string& type) = 0;
};

class CNYPizzaStore : public CPizzaStore
{
protected:

	virtual std::unique_ptr<CPizza> CreatePizza(const std::string& type) override
	{
		using namespace std;
		unique_ptr<CPizza> pizza;
		auto ingredientFactory = make_unique<CNyPizzaIngredientFactory>();
		if (type == "cheese")
		{
			pizza = make_unique<CCheesePizza>(move(ingredientFactory));
			pizza->SetName("New York Style Cheese Pizza");
		}
		else
		{
			/* другие типы пиццы */
		}
		return pizza;
	}

};