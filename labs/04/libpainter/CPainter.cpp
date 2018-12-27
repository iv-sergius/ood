#include "stdafx.h"

#include "CPainter.h"

void CPainter::DrawPicture(const CPictureDraft & picDrafft, ICanvas & canvas)
{
	for (const auto & item : picDrafft)
	{
		item.Draw(canvas);
	}
}
