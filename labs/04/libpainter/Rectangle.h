#pragma once

#include "Shape.h"

class CRectangle : public CShape
{
	SPoint GetLeftTop();
	SPoint GetRightBottom();
};
