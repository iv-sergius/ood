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