#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle(SPoint vertex1, SPoint vertex2, Color color)
	: CShape(color)
	, m_center{ (vertex1.x + vertex2.x) / 2.f, (vertex1.y + vertex2.y) / 2.f }
	, m_width(abs(vertex1.x - vertex2.x))
	, m_height(abs(vertex1.y - vertex2.y))
{
}

SPoint CRectangle::GetLeftTop() const
{
	return SPoint{ m_center.x - m_width / 2.f, m_center.y + m_height / 2.f };
}

SPoint CRectangle::GetRightBottom() const
{
	return SPoint{ m_center.x + m_width / 2.f, m_center.y - m_height / 2.f };
}
