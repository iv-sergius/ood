#pragma once

#include "Shape.h"

class CTriangle : public CShape
{
public:
	SPoint GetVertex1();
	SPoint GetVertex2();
	SPoint GetVertex3();
};
