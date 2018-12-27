#include "stdafx.h"
#include "RegularPolygon.h"
#define _USE_MATH_DEFINES
#include <math.h>

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

void CRegularPolygon::Draw(ICanvas & canvas) const
{
	canvas.SetColor(GetColor());
	for (size_t i = 0; i < m_count; i++)
	{
		float phi = static_cast<float> (2. * M_PI / m_count);
		canvas.DrawLine({ m_center.x + m_radius * sin(i * phi), m_center.y + m_radius * cos( i* phi) }, 
			{ m_center.x + m_radius * sin((i + 1) * phi), m_center.y + m_radius * cos((i + 1) * phi) });
	}
}
