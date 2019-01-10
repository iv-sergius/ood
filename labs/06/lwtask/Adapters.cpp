#pragma once

#include "Adapters.h"

namespace graphics_lib
{

	CGraphicLibCanvasObjestAdapter::CGraphicLibCanvasObjestAdapter(modern_graphics_lib::CModernGraphicsRenderer & renderer)
		: m_renderer(renderer)
	{}
	void CGraphicLibCanvasObjestAdapter::MoveTo(int x, int y)
	{

	}
	// Рисует линию с текущей позиции, передвигая перо в точку x,y 
	void CGraphicLibCanvasObjestAdapter::LineTo(int x, int y)
	{

	}

}
