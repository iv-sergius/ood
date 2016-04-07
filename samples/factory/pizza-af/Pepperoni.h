#pragma once
#include <string>

class IPepperoni
{
public:
	virtual std::string ToString()const = 0;

	virtual ~IPepperoni() = default;
};

class CSlicedPepperoni : public IPepperoni
{
	std::string ToString() const override
	{
		return "Sliced Pepperoni";
	}

};