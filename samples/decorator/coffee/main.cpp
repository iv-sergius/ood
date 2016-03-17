#include <iostream>
#include <string>
#include <memory>
#include <functional>

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

// Лимон
class CLemon : public CCondimentDecorator
{
public:
	CLemon(unique_ptr<IBeverage> && beverage, unsigned quantity = 1)
		: CCondimentDecorator(move(beverage))
		, m_quantity(quantity)
	{}
protected:
	double GetCondimentCost()const override
	{
		return 10 * m_quantity;
	}
	string GetCondimentDescription()const override
	{
		return "Lemon x " + to_string(m_quantity);
	}
private:
	unsigned m_quantity;
};

enum class IceCubeType
{
	Dry,
	Water
};

class CIceCubes : public CCondimentDecorator
{
public:	
	CIceCubes(unique_ptr<IBeverage> && beverage, unsigned quantity, IceCubeType type = IceCubeType::Water)
		: CCondimentDecorator(move(beverage))
		, m_quantity(quantity)
		, m_type(type)
	{}
protected:
	double GetCondimentCost()const override
	{
		return (m_type == IceCubeType::Dry ? 10 : 5) * m_quantity;
	}
	string GetCondimentDescription()const override
	{
		return string(m_type == IceCubeType::Dry ? "Dry" : "Water") + " Ice Cube x " + to_string(m_quantity);
	}
private:
	unsigned m_quantity;
	IceCubeType m_type;
};

enum class SyrupType
{
	Chocolate,
	Maple
};

class CSyrup : public CCondimentDecorator
{
public:
	CSyrup(unique_ptr<IBeverage> && beverage, SyrupType syrupType)
		: CCondimentDecorator(move(beverage))
		, m_syrupType(syrupType)
	{}
protected:
	double GetCondimentCost()const override
	{
		return 15;
	}
	string GetCondimentDescription()const override
	{
		return string(m_syrupType == SyrupType::Chocolate ? "Chocolate" : "Maple") + " syrup";
	}
private:
	SyrupType m_syrupType;
};

class CChocolateCrumbs : public  CCondimentDecorator
{
public:
	CChocolateCrumbs(unique_ptr<IBeverage> && beverage, unsigned quantity)
		:CCondimentDecorator(move(beverage))
		, m_quantity(quantity)
	{

	}
	double GetCondimentCost()const override
	{
		return 2 * m_quantity;
	}
	string GetCondimentDescription()const override
	{
		return "Chocolate crumbs " + to_string(m_quantity) + "g";
	}
private:
		unsigned m_quantity;
};


class CCoconutFlakes : public CCondimentDecorator
{
public:
	CCoconutFlakes(unique_ptr<IBeverage> && beverage, unsigned mass)
		: CCondimentDecorator(move(beverage))
		, m_mass(mass)
	{}

protected:
	double GetCondimentCost()const override
	{
		return 1 * m_mass;
	}
	string GetCondimentDescription()const override
	{
		return "Coconut flakes " + to_string(m_mass) + "g";
	}
private:
	unsigned m_mass;
};

/*
Функциональный объект, создающий лимонную добавку
*/
struct MakeLemon
{
	MakeLemon(unsigned quantity):m_quantity(quantity){}

	auto operator()(unique_ptr<IBeverage> && beverage)const
	{
		return make_unique<CLemon>(move(beverage), m_quantity); 
	}
private:
	unsigned m_quantity;
};

/*
Функция, возвращающая функцию, создающую коричную добавку
*/
function<unique_ptr<IBeverage>(unique_ptr<IBeverage> &&)> MakeCinnamon()
{
	return [] (unique_ptr<IBeverage> && b) {
		return make_unique<CCinnamon>(move(b));
	};
}

/*
Функция, которая возвращает функцию, конструирующую произвольную добавку
Аргументы функции MakeCondiment захватываются возвращаемой функцией и *передаются* 
конструктору указанной добавки следом за декорируемым напитком

Используются variadic templates
*/
template <typename Condiment, typename... Ts>
function<unique_ptr<IBeverage>(unique_ptr<IBeverage>&&)> MakeCondiment(Ts&&...args)
{
	return [=](unique_ptr<IBeverage> && b) mutable {
		return make_unique<Condiment>(move(b), forward<Ts>(args)...);
	};
}

/*
unique_ptr<IBeverage> operator << (unique_ptr<IBeverage> && lhs, const MakeLemon & factory)
{
	return factory(move(lhs));
}

unique_ptr<IBeverage> operator << (unique_ptr<IBeverage> && lhs, const MakeCinnamon & factory)
{
	return factory(move(lhs));
}
*/
template <typename CondimentFactory>
unique_ptr<IBeverage> operator << (unique_ptr<IBeverage> && lhs, const CondimentFactory & factory)
{
	return factory(move(lhs));
}


int main()
{
	auto beverage = make_unique<CCoffee>() 
		<< MakeCondiment<CCinnamon>() 
		<< MakeCondiment<CLemon>(2)
		<< MakeCondiment<CIceCubes>(2, IceCubeType::Dry)
		<< MakeCondiment<CChocolateCrumbs>(2);

	auto milkshakeWithMapleSyrup = make_unique<CMilkshake>()
		<< MakeCondiment<CSyrup>(SyrupType::Maple)
		<< MakeCondiment<CCoconutFlakes>(8);

	/*
	auto coffee = make_unique<CCoffee>();
	auto cinnamon = make_unique<CCinnamon>(move(coffee));
	auto lemon = make_unique<CLemon>(move(cinnamon));
	*/

	cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	cout << milkshakeWithMapleSyrup->GetDescription() << " costs " << milkshakeWithMapleSyrup->GetCost() << endl;
}
