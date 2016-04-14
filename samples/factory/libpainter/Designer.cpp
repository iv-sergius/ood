#include "stdafx.h"
#include "Designer.h"
#include "PictureDraft.h"

using namespace std;

CDesigner::CDesigner()
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

	}
	inputData;
	return CPictureDraft();
}
