#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description, const double cost)
		:m_description(description),
		m_cost(cost)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
	double GetCost()const final
	{
		return m_cost;
	}
private:
	std::string m_description;
	double m_cost;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee", const double cost = 80)
		:CBeverage(description, cost) 
	{}
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(const std::string& description = "Capuccino", const double cost = 80)
		:CCoffee(description, cost) 
	{}
};

class CStandartCapuccino : public CCapuccino
{
public:
	CStandartCapuccino()
		:CCapuccino("Standart Capuccino")
	{}
};


class CBigCapuccino : public CCapuccino
{
public:
	CBigCapuccino()
		:CCapuccino("Big Capuccino", 120)
	{}
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(const std::string& description = "Latte", const double cost = 90)
		:CCoffee(description, cost) 
	{}
};

class CStandartLatte : public CLatte
{
public:
	CStandartLatte()
		:CLatte("Standart Latte", 130)
	{}
};

class CBigLatte : public CLatte
{
public:
	CBigLatte()
		:CLatte("Big Latte", 130)
	{}
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(const std::string& description = "Tea")
		:CBeverage("Tea", 30) 
	{}
};

class CGreenTea : public CTea
{
public:
	CGreenTea()
		:CTea("Green Tea")
	{}
};

class CEarlGreyTea : public CTea
{
public:
	CEarlGreyTea()
		:CTea("Earl Grey Tea")
	{}
};

class COolongTea : public CTea
{
public:
	COolongTea()
		:CTea("Oolong Tea")
	{}
};

class CPuerTea : public CTea
{
public:
	CPuerTea()
		:CTea("Puer Tea")
	{}
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(const std::string& description = "Milkshake", const double cost = 80)
		:CBeverage("Milkshake", 80) 
	{}
};

class CSmallMilkshake : public CMilkshake
{
public:
	CSmallMilkshake()
		:CMilkshake("Small Milkshake", 50)
	{}
};

class CStandartMilkshake : public CMilkshake
{
public:
	CStandartMilkshake()
		:CMilkshake("Standart Milkshake", 60)
	{}
};

class CBigMilkshake : public CMilkshake
{
public:
	CBigMilkshake()
		:CMilkshake("Big Milkshake", 80)
	{}
};
