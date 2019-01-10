#pragma once
#include <stdexcept>
#include <exception>

#include "shape_drawing_lib.h"

// ѕространство имен библиотеки дл€ рисовани€ фигур (использует graphics_lib)
//  од библиотеки недоступен дл€ изменени€
namespace shape_drawing_lib
{

	CTriangle::	CTriangle(const Point & p1, const Point & p2, const Point & p3)
	{
		m_vertex1 = p1;
		m_vertex2 = p2;
		m_vertex3 = p3;
	}

	void CTriangle::Draw(graphics_lib::ICanvas & canvas)const
	{
		canvas.MoveTo(m_vertex1.x, m_vertex1.y);
		canvas.LineTo(m_vertex2.x, m_vertex2.y);
		canvas.LineTo(m_vertex3.x, m_vertex3.y);
		canvas.LineTo(m_vertex1.x, m_vertex1.y);
	}

	CRectangle::CRectangle(const Point & leftTop, int width, int height)
	{
		m_leftTop = leftTop;
		m_width = width >= 0 ? width : throw std::invalid_argument("Width must be non-negative");
		m_height = height >= 0 ? height : throw std::invalid_argument("Width must be non-negative");
	}

	void CRectangle::Draw(graphics_lib::ICanvas & canvas)const
	{
		canvas.MoveTo(m_leftTop.x, m_leftTop.y);
		canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
		canvas.LineTo(m_leftTop.x, m_leftTop.y);
	}

	CCanvasPainter::CCanvasPainter(graphics_lib::ICanvas & canvas)
	{
		m_canvas = &canvas;
	}
	void CCanvasPainter::Draw(const ICanvasDrawable & drawable)
	{
		drawable.Draw(*m_canvas);
	}
}

