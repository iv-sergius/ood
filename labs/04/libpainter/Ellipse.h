#pragma once

#include "Shape.h"

class CEllipse : public CShape
{
public:
	CEllipse(SPoint center, float gorizontalRadius, float verticalRadius, Color color);
	SPoint GetCenter() const;
	float GetHorizontalRadius() const;
	float GetVerticalRadius() const;
private:
	SPoint m_center;
	float m_gorizontalR;
	float m_verticalR;
};
