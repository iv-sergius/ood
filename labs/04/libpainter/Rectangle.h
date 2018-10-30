#pragma once

#include "Shape.h"

class CRectangle : public CShape
{
public:
	CRectangle(SPoint leftTop, SPoint rigthBottom, Color color);
	SPoint GetLeftTop();
	SPoint GetRightBottom();
private:
	SPoint m_center;
	float m_width;
	float m_height;
};
