#pragma once
#include "Clams.h"
#include "Dough.h"
#include "Cheese.h"
#include "Veggies.h"
#include "Pepperoni.h"
#include "Sauce.h"
#include <memory>
#include <vector>

class IPizzaIngredientFactory
{
public:
	virtual std::unique_ptr<IDough> CreateDough() = 0;
	virtual std::unique_ptr<ISauce> CreateSauce() = 0;
	virtual std::unique_ptr<ICheese> CreateCheese() = 0;
	virtual std::vector<std::unique_ptr<IVeggies>> CreateVeggies() = 0;
	virtual std::unique_ptr<IPepperoni> CreatePepperoni() = 0;
	virtual std::unique_ptr<IClams> CreateClam() = 0;

	virtual ~IPizzaIngredientFactory() = default;
};