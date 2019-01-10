#include "graphics_lib.h"
#include <iostream>

using namespace std;

// ѕространство имен графической библиотеки (недоступно дл€ изменени€)
namespace graphics_lib
{

void CCanvas::MoveTo(int x, int y)
{
	cout << "MoveTo (" << x << ", " << y << ")" << endl;
}
void CCanvas::LineTo(int x, int y)
{
	cout << "LineTo (" << x << ", " << y << ")" << endl;
}

}
