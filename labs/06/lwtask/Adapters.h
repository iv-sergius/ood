#pragma once

#include "graphics_lib.h"
#include "modern_graphics_lib.h"

namespace adapter
{

	class CGraphicLibObjectAdapter : public graphics_lib::ICanvas
	{
	public:
		CGraphicLibObjectAdapter(modern_graphics_lib::CModernGraphicsRenderer & renderer);
		void MoveTo(int x, int y);
		void LineTo(int x, int y);
		~CGraphicLibObjectAdapter();
	private:
		modern_graphics_lib::CModernGraphicsRenderer & m_renderer;
		modern_graphics_lib::CPoint m_lastPoint;
	};

	class CGraphicsLibClassAdapter : public modern_graphics_lib::CModernGraphicsRenderer, virtual public graphics_lib::ICanvas
	{
		CGraphicsLibClassAdapter(modern_graphics_lib::CModernGraphicsRenderer & renderer);
		void MoveTo(int x, int y);
		void LineTo(int x, int y);
	private:
		modern_graphics_lib::CModernGraphicsRenderer & m_renderer;
		modern_graphics_lib::CPoint m_lastPoint;
	};

}
