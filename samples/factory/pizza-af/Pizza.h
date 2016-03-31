#pragma once
#include "Cheese.h"
#include "Clams.h"
#include "Dough.h"
#include "Pepperoni.h"
#include "Sauce.h"
#include "Veggies.h"

#include <memory>
#include <vector>
#include <iostream>


class CPizza
{
public:

	virtual void Prepare() = 0;

	CPizza(const std::string & name)
		:m_name(name)
	{
	}

	void Bake()
	{
		std::cout << "Bake for 25 minutes at 350" << std::endl;
	}

	void Cut()
	{
		std::cout << "Cutting the pizza into diagonal slices" << std::endl;
	}

	void Box() 
	{
		std::cout << "Place pizza in official PizzaStore box" << std::endl;
	}

	std::string GetName()const
	{
		return m_name;
	}

	std::string ToString()const
	{
		std::string result;
		result.append("---- " + m_name + " ----\n");
		if (m_dough)
		{
			result.append(m_dough->ToString() + "\n");
		}
		if (m_sauce)
		{
			result.append(m_sauce->ToString() + "\n");
		}
		if (m_cheese)
		{
			result.append(m_cheese->ToString() + "\n");
		}

		for (auto & v : m_veggies)
		{
			result.append(v->ToString() + ", ");
		}
		if (m_clam)
		{
			result.append(m_clam->ToString() + "\n");
		}
		if (m_pepperoni)
		{
			result.append(m_pepperoni->ToString() + "\n");
		}
		return result;
	}


	virtual ~CPizza() = default;
protected:
	std::string m_name;
	std::unique_ptr<IDough> m_dough;
	std::unique_ptr<ISauce> m_sauce;
	std::vector<std::unique_ptr<IVeggies>> m_veggies;
	std::unique_ptr<ICheese> m_cheese;
	std::unique_ptr<IPepperoni> m_pepperoni;
	std::unique_ptr<IClams> m_clam;
};

class CCheesePizza : public CPizza
{
	// Тесто
	// Соус
	// Сыр
};