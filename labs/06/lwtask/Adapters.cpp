#pragma once
#include "stdafx.h"

#include "Adapters.h"

//using namespace modern_graphics_lib;

namespace adapter
{
	CGraphicLibObjectAdapter::CGraphicLibObjectAdapter(modern_graphics_lib::CModernGraphicsRenderer & renderer)
		: m_renderer(renderer)
		, m_lastPoint(modern_graphics_lib::CPoint(0, 0))
	{
		m_renderer.BeginDraw();
	}
	void CGraphicLibObjectAdapter::MoveTo(int x, int y)
	{
		m_lastPoint = modern_graphics_lib::CPoint(x, y);
	}
	// Рисует линию с текущей позиции, передвигая перо в точку x,y 
	void CGraphicLibObjectAdapter::LineTo(int x, int y)
	{
		m_renderer.DrawLine(m_lastPoint, modern_graphics_lib::CPoint(x, y));
		m_lastPoint = modern_graphics_lib::CPoint(x, y);
	}
	CGraphicLibObjectAdapter::~CGraphicLibObjectAdapter()
	{
		m_renderer.EndDraw();
	}

	void CGraphicsLibClassAdapter::MoveTo(int x, int y)
	{
	}
	void CGraphicsLibClassAdapter::LineTo(int x, int y)
	{
	}
}
