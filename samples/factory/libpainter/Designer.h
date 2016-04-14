#pragma once
#include <iosfwd>

class CPictureDraft;

class CDesigner
{
public:
	CDesigner();
	~CDesigner();
	CPictureDraft CreateDraft(std::istream & inputData);
};

