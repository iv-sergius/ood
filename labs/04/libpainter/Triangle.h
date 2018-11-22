#pragma once

#include "Shape.h"

class CTriangle : public CShape
{
public:
	CTriangle(SPoint vertex1, SPoint vertex2, SPoint vertex3, Color color);
	SPoint GetVertex1() const;
	SPoint GetVertex2() const;
	SPoint GetVertex3() const;
private:
	SPoint m_vertex1;
	SPoint m_vertex2;
	SPoint m_vertex3;
};
