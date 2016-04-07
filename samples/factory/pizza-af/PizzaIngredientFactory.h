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

class CNyPizzaIngredientFactory : public IPizzaIngredientFactory
{
	std::unique_ptr<IDough> CreateDough() override
	{
		return std::make_unique<CThinCrustDough>();
	}

	std::unique_ptr<ISauce> CreateSauce() override
	{
		return std::make_unique<CMarinaraSauce>();
	}

	std::unique_ptr<ICheese> CreateCheese() override
	{
		return std::make_unique<CReggianoCheese>();
	}

	std::vector<std::unique_ptr<IVeggies>> CreateVeggies() override
	{
		using std::make_unique;
		return { make_unique<CGarlic>(), make_unique<COnion>(), 
			make_unique<CMushroom>(), make_unique<CRedPepper>()
		};
	}

	std::unique_ptr<IPepperoni> CreatePepperoni() override
	{
		return std::make_unique<CSlicedPepperoni>();
	}

	std::unique_ptr<IClams> CreateClam() override
	{
		return std::make_unique<CFreshClams>();
	}
};