#pragma once

#include "Shape.h"

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(uint32_t vertexCount, SPoint center, float radius, Color color);
	uint32_t GetVertexCount();
	SPoint GetCenter();
	float GetRadius();
private:
	uint32_t m_count;
	SPoint m_center;
	float m_radius;
};
