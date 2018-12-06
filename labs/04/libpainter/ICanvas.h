#pragma once

#include "GeneralGraphics.h"

class ICanvas
{
public:
	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(const SPoint & from, const SPoint & to) = 0;
	virtual void DrawEllipse(const float left, const float top, const float width, const float height) = 0;

	virtual ~ICanvas() = default;
};