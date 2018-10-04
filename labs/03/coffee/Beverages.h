#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description)
	{}

	double GetCost() const override
	{
		return 60;
	}
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(const std::string& description = "Capuccino")
		:CCoffee(description)
	{}

	double GetCost() const override
	{
		return 80;
	}
};

class CStandartCapuccino : public CCapuccino
{
public:
	CStandartCapuccino()
		:CCapuccino("Standart Capuccino")
	{}

	double GetCost() const override
	{
		return 80;
	}
};

class CBigCapuccino : public CCapuccino
{
public:
	CBigCapuccino()
		:CCapuccino("Big Capuccino")
	{}

	double GetCost() const override
	{
		return 120;
	}
};


// Латте
class CLatte : public CCoffee
{
public:
	CLatte(const std::string& description = "Latte")
		:CCoffee(description)
	{}

	double GetCost() const override
	{
		return 90;
	}
};

class CStandartLatte : public CLatte
{
public:
	CStandartLatte()
		:CLatte("Standart Latte")
	{}

	double GetCost() const override
	{
		return 90;
	}
};

class CBigLatte : public CLatte
{
public:
	CBigLatte()
		:CLatte("Big Latte")
	{}

	double GetCost() const override
	{
		return 130;
	}
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(const std::string& description = "Tea")
		:CBeverage(description)
	{}

	double GetCost() const override
	{
		return 30;
	}
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
	CMilkshake(const std::string& description = "Milkshake")
		:CBeverage(description)
	{}

	double GetCost() const override
	{
		return 80;
	}
};


class CSmallMilkshake : public CMilkshake
{
public:
	CSmallMilkshake()
		:CMilkshake("Small Milkshake")
	{}

	double GetCost() const override
	{
		return 50;
	}
};

class CStandartMilkshake : public CMilkshake
{
public:
	CStandartMilkshake()
		:CMilkshake("Standart Milkshake")
	{}

	double GetCost() const override
	{
		return 60;
	}
};

class CBigMilkshake : public CMilkshake
{
public:
	CBigMilkshake()
		:CMilkshake("Big Milkshake")
	{}

	double GetCost() const override
	{
		return 80;
	}
};
