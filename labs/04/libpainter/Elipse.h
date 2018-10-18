#pragma once

#include "Shape.h"

class CElipse : public CShape
{
public:
	SPoint GetCenter();
	float GetHorizontalRadius();
	float GetVerticalRadius();
};
