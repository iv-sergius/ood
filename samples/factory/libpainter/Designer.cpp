#include "stdafx.h"
#include "Designer.h"
#include "PictureDraft.h"
#include "IShapeFactory.h"

using namespace std;

CDesigner::CDesigner(IShapeFactory & factory)
	:m_factory(factory)
{
}


CDesigner::~CDesigner()
{
}

CPictureDraft CDesigner::CreateDraft(std::istream & inputData)
{
	string line;
	while (getline(inputData, line))
	{
		m_factory.CreateShape(line);
	}
	inputData;
	return CPictureDraft();
}
