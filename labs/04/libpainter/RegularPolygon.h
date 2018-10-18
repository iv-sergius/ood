#pragma once

#include "Shape.h"

class CRegularPolygon : public CShape
{
public:
	size_t GetVertexCount();
	SPoint GetCenter();
	float GetRadius();
};
