#include <iostream>
#include <string>

using namespace std;

namespace basic
{

class CCoffee
{
public:
	void PrepareRecipe()
	{
		BoilWater();
		BrewCoffeeGrinds();
		PourInCup();
		AddSugarAndMilk();
	}
	
	void BoilWater()
	{
		cout << "Boiling water" << endl;
	}

	void BrewCoffeeGrinds()
	{
		cout << "Dripping Coffee through filter" << endl;
	}

	void PourInCup()
	{
		cout << "Pouring into cup" << endl;
	}

	void AddSugarAndMilk()
	{
		cout << "Adding sugar and milk" << endl;
	}
};

class CTea
{
public:
	void PrepareRecipe()
	{
		BoilWater();
		SteepTeaBag();
		PourInCup();
		AddLemon();
	}

	void BoilWater()
	{
		cout << "Boiling water" << endl;
	}

	void SteepTeaBag()
	{
		cout << "Steeping the tea" << endl;
	}

	void PourInCup()
	{
		cout << "Pouring into cup" << endl;
	}

	void AddLemon()
	{
		cout << "Adding Lemon" << endl;
	}
};

}

namespace naive
{

class CCaffeineBeverage
{
public:
	virtual void PrepareRecipe() = 0;

	void BoilWater()
	{
		cout << "Boiling water" << endl;
	}

	void PourInCup()
	{
		cout << "Pouring into cup" << endl;
	}

	virtual ~CCaffeineBeverage() = default;
};

class CCoffee : public CCaffeineBeverage
{
public:
	void PrepareRecipe() override
	{
		BoilWater();
		BrewCoffeeGrinds();
		PourInCup();
		AddSugarAndMilk();
	}

	void BrewCoffeeGrinds()
	{
		cout << "Dripping Coffee through filter" << endl;
	}

	void AddSugarAndMilk()
	{
		cout << "Adding sugar and milk" << endl;
	}
};

class CTea : public CCaffeineBeverage
{
public:
	void PrepareRecipe() override
	{
		BoilWater();
		SteepTeaBag();
		PourInCup();
		AddLemon();
	}

	void SteepTeaBag()
	{
		cout << "Steeping the tea" << endl;
	}

	void AddLemon()
	{
		cout << "Adding Lemon" << endl;
	}
};

}

namespace template_method
{

class CCaffeineBeverage
{
public:
	void PrepareRecipe()
	{
		BoilWater();
		Brew();
		PourInCup();
		AddCondiments();
	}

	void BoilWater()
	{
		cout << "Boiling water" << endl;
	}

	void PourInCup()
	{
		cout << "Pouring into cup" << endl;
	}

	virtual void Brew() = 0;
	virtual void AddCondiments() = 0;
	virtual ~CCaffeineBeverage() = default;
};

class CCoffee : public CCaffeineBeverage
{
public:
	void Brew() override
	{
		cout << "Dripping Coffee through filter" << endl;
	}

	void AddCondiments() override
	{
		cout << "Adding sugar and milk" << endl;
	}
};

class CTea : public CCaffeineBeverage
{
public:
	void Brew() override
	{
		cout << "Steeping the tea" << endl;
	}

	void AddCondiments() override
	{
		cout << "Adding Lemon" << endl;
	}
};

}

namespace template_method_structure
{

class CAbstractClass
{
public:
	void TemplateMethod()
	{
		PrimitiveOperation1();
		PrimitiveOperation2();
		ConcreteOperation1();
		ConcreteOperation2();
		Hook();
	}

	virtual void PrimitiveOperation1() = 0;
	virtual void PrimitiveOperation2() = 0;

	virtual void ConcreteOperation1()
	{
		// реализация
	}

	void ConcreteOperation2()
	{
		// Реализация
	}

	virtual void Hook()	{}
};

}

namespace hooks
{

class CCaffeineBeverageWithHook
{
public:
	void PrepareRecipe()
	{
		BoilWater();
		Brew();
		PourInCup();
		if (CustomerWantsCondiments())
		{
			AddCondiments();
		}
	}

	void BoilWater()
	{
		cout << "Boiling water" << endl;
	}

	void PourInCup()
	{
		cout << "Pouring into cup" << endl;
	}

	virtual bool CustomerWantsCondiments()
	{
		return true;
	}

	virtual void Brew() = 0;
	virtual void AddCondiments() = 0;
	virtual ~CCaffeineBeverageWithHook() = default;
};

class CCoffeeWithHook : public CCaffeineBeverageWithHook
{
public:
	void Brew() override
	{
		cout << "Dripping Coffee through filter" << endl;
	}
	void AddCondiments() override
	{
		cout << "Adding sugar and milk" << endl;
	}

	bool CustomerWantsCondiments() override
	{
		cout << "Would you like milk and sugar with your coffee (y/n)? ";
		string userInput;
		return getline(cin, userInput) 
			&& (userInput == "y" || userInput == "Y");
	}
};

void Test()
{
	CCoffeeWithHook coffeeHook;
	coffeeHook.PrepareRecipe();
}

}

void main()
{
	hooks::Test();
}
