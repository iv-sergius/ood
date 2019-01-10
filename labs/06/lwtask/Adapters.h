#pragma once

#include "graphics_lib.h"
#include "modern_graphics_lib.h"

namespace graphics_lib
{

	class CGraphicLibCanvasObjestAdapter : public ICanvas
	{
		CGraphicLibCanvasObjestAdapter(modern_graphics_lib::CModernGraphicsRenderer & renderer);
		void MoveTo(int x, int y);
		void LineTo(int x, int y);
		~CGraphicLibCanvasObjestAdapter() = default;
	private:
		modern_graphics_lib::CModernGraphicsRenderer & m_renderer;
	};

}
