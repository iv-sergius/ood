#pragma once

#include "Shape.h"

class CRectangle : public CShape
{
public:
	CRectangle(SPoint leftTop, SPoint rigthBottom, Color color);
	SPoint GetLeftTop() const;
	SPoint GetRightBottom() const;
	void Draw(ICanvas & canvas);
private:
	SPoint m_center;
	float m_width;
	float m_height;
};
