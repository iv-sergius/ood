#pragma once

#include <string>

class IVeggies
{
public:
	virtual std::string ToString()const = 0;

	virtual ~IVeggies() = default;
};

class CBlackOlives : public IVeggies 
{
public:
	std::string ToString() const override
	{
		return "Black Olives";
	}
};
