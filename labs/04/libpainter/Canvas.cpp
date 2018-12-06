#include "stdafx.h"

#include "CCanvas.h"

void CCanvas::SetColor(Color color)
{
	m_outStream << color << std::endl;
}

void CCanvas::DrawLine(const SPoint & from, const SPoint & to)
{
	m_outStream << from.x << from.y << to.x << to.y << std::endl;
}

void CCanvas::DrawEllipse(const float left, const float top, const float width, const float height)
{
	m_outStream << left << top << width << height << std::endl;
}
