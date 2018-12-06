#pragma once

#include "ICanvas.h"
#include "GeneralGraphics.h"

class CShape
{
public:
	CShape() = default;
	CShape(Color color);
	virtual ~CShape() = default;
	Color GetColor() const;
		
	void Draw(ICanvas & canvas);
private:
	Color m_color;
};

