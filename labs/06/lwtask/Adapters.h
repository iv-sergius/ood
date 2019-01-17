#pragma once

#include "graphics_lib.h"
#include "modern_graphics_lib.h"

namespace graphics_lib
{

	class CGraphicLibObjectAdapter : public ICanvas
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

}
