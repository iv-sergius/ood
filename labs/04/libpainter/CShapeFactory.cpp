#include "stdafx.h"

#include "CShapeFactory.h"

#include "Shape.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "RegularPolygon.h"
#include "Triangle.h"

std::unique_ptr<CShape> CShapeFactory::CreateShape(const std::string & description)
{
	std::unique_ptr<CShape> ptr;
	if (description.compare("Ellipse") == 0)
	{
		ptr = std::make_unique<CEllipse>(SPoint{ 1.f, 2.f }, 2.f, 3.f, Color::Black);
	}
	ptr = std::make_unique<CShape>();
	return ptr;
}