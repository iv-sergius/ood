// Painter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/CShapeFactory.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/CCanvas.h"
#include "../libpainter/CPainter.h"
#include <fstream>

using namespace std;

int main()
{
	try
	{
		CShapeFactory factory;
		CDesigner designer(factory);

		std::string figueDesc;

		CPictureDraft picDraft = designer.CreateDraft(std::cin);

		CCanvas canvas;

		CPainter painter;
		painter.DrawPicture(picDraft, canvas);

		ofstream outFile("out.svg");

		canvas.Show(outFile);

	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	return 0;
}

