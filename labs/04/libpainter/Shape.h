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
	CShape() = default;
	CShape(Color color);
	virtual ~CShape() = default;
	Color GetColor() const;
private:
	Color m_color;
};

