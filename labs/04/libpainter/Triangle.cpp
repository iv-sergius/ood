#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle(SPoint vertex1, SPoint vertex2, SPoint vertex3, Color color)
	: CShape(color)
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

SPoint CTriangle::GetVertex1()
{
	return SPoint();
}

SPoint CTriangle::GetVertex2()
{
	return SPoint();
}

SPoint CTriangle::GetVertex3()
{
	return SPoint();
}
