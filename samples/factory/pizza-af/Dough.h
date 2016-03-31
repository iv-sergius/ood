#pragma once

#include <string>

class IDough
{
public:
	virtual std::string ToString()const = 0;

	virtual ~IDough() = default;
};
