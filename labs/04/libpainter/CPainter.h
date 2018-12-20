#pragma once

#include "IPainter.h"

struct CPainter : public IPainter
{
	void DrawPicture(const CPictureDraft & picDrafft, ICanvas & canvas) override;
};