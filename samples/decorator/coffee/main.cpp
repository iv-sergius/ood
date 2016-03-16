#include <iostream>
#include <string>

using namespace std;

// Абстрактный напиток
class IBeverage
{
public:
	virtual string GetDescription() const = 0;	// Название
	virtual double GetCost()const = 0;			// Стоимость
	virtual void SetChocolateSyrup(bool hasSyrup) = 0;
	virtual void HasChocolateSyrup()const = 0;
	virtual ~IBeverage() = default;
};

class CBeverage : public IBeverage
{
public:
	string GetDescription()const override
	{
		string desc;
		if (m_hasChocolateCrumbs) desc += ", chocolate crumbs";
		// ...
		return desc;
	}
	double GetCost()const override
	{
		double cost = 0;
		if (m_hasChocolateSyrup) cost += 30;
		// ...
		return cost;
	}
	virtual void SetChocolateSyrup(bool hasSyrup) override final
	{
		m_hasChocolateSyrup = hasSyrup;
	}
	virtual void HasChocolateSyrup()const override final
	{
		return m_hasChocolateSyrup
	}
	/*  остальные методы */
private:
	bool m_hasChocolateSyrup = false;
	bool m_hasCinnamon = false;
	bool m_hasLemon = false;
	bool m_hasIce = false;
	bool m_hasChocolateCrumbs = false;
	bool m_hasCoconutFlakes = false;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	string GetDescription() const override { return "Coffee" + CBeverage::GetDescription(); }
	double GetCost() const { return 60 + CBeverage::GetCost(); }
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	string GetDescription() const override { return "Capuccino"; }
	double GetCost() const { return 80; }
};

// Латте
class CLatte : public CCoffee
{
public:
	string GetDescription() const override { return "Latte"; }
	double GetCost() const { return 90; }
};

// Чай
class CTea : public IBeverage
{
public:
	string GetDescription() const override { return "Tea"; }
	double GetCost() const override { return 30; }
};

// Молочный коктейль
class CMilkshake : public IBeverage
{
public:
	string GetDescription() const override { return "Milkshake"; }
	double GetCost() const override { return 80; }
};


int main()
{

}
