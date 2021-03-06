#include "stdafx.h"
#include "Shape.h"


CShape::CShape(Color color)
	: m_color(color)
{
}

Color CShape::GetColor() const
{
	return m_color;
}

void CShape::Draw(ICanvas & canvas) const
{
	canvas.SetColor(GetColor());
}
