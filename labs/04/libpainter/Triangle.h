#pragma once

#include "Shape.h"

class CTriangle : public CShape
{
public:
	CTriangle(SPoint vertex1, SPoint vertex2, SPoint vertex3, Color color);
	SPoint GetVertex1();
	SPoint GetVertex2();
	SPoint GetVertex3();
private:
	SPoint m_vertex1;
	SPoint m_vertex2;
	SPoint m_vertex3;
};
