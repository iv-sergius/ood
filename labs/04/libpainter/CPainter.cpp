#include "stdafx.h"

#include "CPainter.h"

void CPainter::DrawPicture(const CPictureDraft & picDrafft, ICanvas & canvas)
{
	//for (auto item : picDrafft) // convert from *CShape to CShape
	for (auto iter = picDrafft.begin(); iter != picDrafft.end(); iter++)
	{
		//item.Draw(canvas);
		(*iter).Draw(canvas);
	}
}
