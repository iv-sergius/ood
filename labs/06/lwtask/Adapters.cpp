#pragma once

#include "Adapters.h"

//using namespace modern_graphics_lib;

namespace graphics_lib
{
	CGraphicLibObjestAdapter::CGraphicLibObjestAdapter(modern_graphics_lib::CModernGraphicsRenderer & renderer)
		: m_renderer(renderer)
		, m_lastPoint(modern_graphics_lib::CPoint(0, 0))
	{}
	void CGraphicLibObjestAdapter::MoveTo(int x, int y)
	{
	}
	// Рисует линию с текущей позиции, передвигая перо в точку x,y 
	void CGraphicLibObjestAdapter::LineTo(int x, int y)
	{
		m_renderer.DrawLine(m_lastPoint, modern_graphics_lib::CPoint(x, y));
		m_lastPoint = modern_graphics_lib::CPoint(x, y);
	}

}
