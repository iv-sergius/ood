#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle(SPoint vertex1, SPoint vertex2, Color color)
	: CShape(color)
	, m_center{ (vertex1.x + vertex2.x) / 2, (vertex1.y + vertex2.y) / 2 }
{
}

SPoint CRectangle::GetLeftTop()
{
	return SPoint();
}

SPoint CRectangle::GetRightBottom()
{
	return SPoint();
}
