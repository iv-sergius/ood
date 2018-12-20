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
		
	virtual void Draw(ICanvas & canvas) const;
private:
	Color m_color;
};

