#pragma once
#include <string>

class ICheese
{
public:
	virtual std::string ToString()const = 0;

	virtual ~ICheese() = default;
};