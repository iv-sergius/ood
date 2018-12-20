#pragma once

#include "ICanvas.h"
#include <iostream>

class CCanvas : public ICanvas
{
public:
	CCanvas() = default;
	void Clear();
	void SetColor(Color color);
	void DrawLine(const SPoint & from, const SPoint & to);
	void DrawEllipse(const float left, const float top, const float width, const float height);
	void Show(std::ostream & outStream);
private:
	std::string m_str;
	Color m_color;
};