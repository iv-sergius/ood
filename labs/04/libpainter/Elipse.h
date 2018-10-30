#pragma once

#include "Shape.h"

class CElipse : public CShape
{
public:
	CElipse(SPoint center, float gorizontalRadius, float verticalRadius, Color color);
	SPoint GetCenter();
	float GetHorizontalRadius();
	float GetVerticalRadius();
private:
	SPoint m_center;
	float m_gorizontalR;
	float m_verticalR;
};
