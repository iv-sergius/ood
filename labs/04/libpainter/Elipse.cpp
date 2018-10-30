#include "stdafx.h"
#include "Elipse.h"

CElipse::CElipse(SPoint center, float gorizontalRadius, float verticalRadius, Color color)
	: CShape(color)
	, m_center(center)
	, m_gorizontalR(gorizontalRadius)
	, m_verticalR(verticalRadius)
{
	if (gorizontalRadius < 0.)
	{
		throw std::invalid_argument("Gorizontal radius must be non-negative");
	}
	if (verticalRadius < 0.)
	{
		throw std::invalid_argument("Vertical radius must be non-negative");
	}
}

SPoint CElipse::GetCenter()
{
	return m_center;
}

float CElipse::GetHorizontalRadius()
{
	return m_gorizontalR;
}

float CElipse::GetVerticalRadius()
{
	return m_verticalR;
}
