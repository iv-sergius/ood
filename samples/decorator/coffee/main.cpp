#include <iostream>
#include <string>
#include <memory>

using namespace std;

// Абстрактный напиток
class IBeverage
{
public:
	virtual string GetDescription() const = 0;
	virtual double GetCost()const = 0;
	virtual ~IBeverage() = default;
};

class CBeverage : public IBeverage
{
public:
	CBeverage(const string & description)
		:m_description(description)
	{}

	string GetDescription()const override final
	{
		return m_description;
	}
private:
	string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const string& description = "Coffee") :CBeverage(description) {}
	double GetCost() const override { return 60; }
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino() :CCoffee("Capuccino") {}
	double GetCost() const override { return 80; }
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte() :CCoffee("Latte") {}
	double GetCost() const override { return 90; }
};

// Чай
class CTea : public CBeverage
{
public:
	CTea() :CBeverage("Tea") {}
	double GetCost() const override { return 30; }
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake() :CBeverage("Milkshake") {}
	double GetCost() const override { return 80; }
};

// Декоратор "добавка к напитку"
class CCondimentDecorator : public IBeverage
{
public:
	string GetDescription()const override
	{
		return m_beverage->GetDescription() + ", " + GetCondimentDescription();
	}
	double GetCost()const override
	{
		return m_beverage->GetCost() + GetCondimentCost();
	}
protected:
	CCondimentDecorator(unique_ptr<IBeverage> && beverage)
		: m_beverage(move(beverage))
	{
	}
	virtual string GetCondimentDescription()const = 0;
	virtual double GetCondimentCost()const = 0;
private:
	unique_ptr<IBeverage> m_beverage;
};

// Корица
class CCinnamon : public CCondimentDecorator
{
public:
	CCinnamon(unique_ptr<IBeverage> && beverage) 
		: CCondimentDecorator(move(beverage)) 
	{}
protected:
	double GetCondimentCost()const override
	{
		return 20;
	}
	string GetCondimentDescription()const override
	{
		return "Cinnamon";
	}
};

int main()
{
	auto coffee = make_unique<CCoffee>();
	auto cinnamon = make_unique<CCinnamon>(move(coffee));
	cout << cinnamon->GetDescription() << " costs " << cinnamon->GetCost() << endl;
}
