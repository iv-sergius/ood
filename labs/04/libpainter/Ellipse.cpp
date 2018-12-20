#include "stdafx.h"
#include "Ellipse.h"

CEllipse::CEllipse(SPoint center, float gorizontalRadius, float verticalRadius, Color color)
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

SPoint CEllipse::GetCenter() const
{
	return m_center;
}

float CEllipse::GetHorizontalRadius() const
{
	return m_gorizontalR;
}

float CEllipse::GetVerticalRadius() const
{
	return m_verticalR;
}

void CEllipse::Draw(ICanvas & canvas) const
{
	canvas.SetColor(GetColor());
}