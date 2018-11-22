#include "stdafx.h"
#include "RegularPolygon.h"

CRegularPolygon::CRegularPolygon(uint32_t vertexCount, SPoint center, float radius, Color color)
	: CShape(color)
	, m_count(vertexCount)
	, m_center(center)
	, m_radius(radius)
{
	if (vertexCount < 3)
	{
		throw std::invalid_argument("VertexCount must be at least 3");
	}
	if (radius < 0.f)
	{
		throw std::invalid_argument("Radius must be non-negative");
	}
}

uint32_t CRegularPolygon::GetVertexCount() const
{
	return m_count;
}

SPoint CRegularPolygon::GetCenter() const
{
	return m_center;
}

float CRegularPolygon::GetRadius() const
{
	return m_radius;
}
