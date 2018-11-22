#pragma once

#include "IShapeFactory.h"

struct CShapeFactory : public IShapeFactory
{
public:
	std::unique_ptr<CShape> CreateShape(const std::string & description) override;
};