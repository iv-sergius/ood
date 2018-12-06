#pragma once

#include "ICanvas.h"
#include <iostream>

class CCanvas : public ICanvas
{
public:
	CCanvas(std::ostream & outStream);
	void SetColor(Color color);
	void DrawLine(const SPoint & from, const SPoint & to);
	void DrawEllipse(const float left, const float top, const float width, const float height);
private:
	std::ostream m_outStream;
};