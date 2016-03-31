#pragma once
#include <string>

class IClams
{
public:
	virtual std::string ToString()const = 0;

	virtual ~IClams() = default;
};

// CFreshClams