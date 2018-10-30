#include "stdafx.h"
#include "RegularPolygon.h"

CRegularPolygon::CRegularPolygon(uint32_t vertexCount, SPoint center, float radius, Color color)
	: CShape(color)
	, m_count(vertexCount)
	, m_center(center)
	, m_radius(radius)
{
}

uint32_t CRegularPolygon::GetVertexCount()
{
	return size_t();
}

SPoint CRegularPolygon::GetCenter()
{
	return SPoint();
}

float CRegularPolygon::GetRadius()
{
	return 0.0f;
}
