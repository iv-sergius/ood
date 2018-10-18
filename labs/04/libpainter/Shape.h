#pragma once

enum Color
{
	Green,
	Red,
	Blue,
	Yellow,
	Pink,
	Black,
};

struct SPoint
{
	float x;
	float y;
};

class CShape
{
public:
	CShape();
	virtual ~CShape();
};

