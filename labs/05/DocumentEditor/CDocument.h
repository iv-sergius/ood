#pragma once

#include "IDocument.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(const string& text);
	string GetText() const;
	void SetText(const string& text);
private:
	string m_text;
};

class CImage : public IImage
{

};

class CDocument : public IDocument
{

};