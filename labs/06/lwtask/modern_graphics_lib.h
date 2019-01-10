#pragma once

#include <iostream>

using namespace std;

// ������������ ���� ����������� ����������� ���������� (���������� ��� ���������)
namespace modern_graphics_lib
{
	class CPoint
	{
	public:
		CPoint(int x, int y) :x(x), y(y) {}

		int x;
		int y;
	};

	// ����� ��� ������������ ��������� �������
	class CModernGraphicsRenderer
	{
	public:
		CModernGraphicsRenderer(ostream & strm);
		~CModernGraphicsRenderer();
		// ���� ����� ������ ���� ������ � ������ ���������
		void BeginDraw();
		// ��������� ��������� �����
		void DrawLine(const CPoint & start, const CPoint & end);
		// ���� ����� ������ ���� ������ � ����� ���������
		void EndDraw();
	private:
		ostream & m_out;
		bool m_drawing = false;
	};
}
