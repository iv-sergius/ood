#include "stdafx.h"
#include "Elipse.h"

CElipse::CElipse(SPoint center, float gorizontalRadius, float verticalRadius, Color color)
	: CShape(color)
	, m_center(center)
	, m_gorizontalR(gorizontalRadius)
	, m_verticalR(verticalRadius)
{
}

SPoint CElipse::GetCenter()
{
	return SPoint();
}

float CElipse::GetHorizontalRadius()
{
	return 0.0f;
}

float CElipse::GetVerticalRadius()
{
	return 0.0f;
}
