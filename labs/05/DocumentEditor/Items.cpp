#include "CDocument.h"

CParagraph::CParagraph(const string& text)
	: m_text(text)
{}

string CParagraph::GetText() const
{
	return m_text;
}

void CParagraph::SetText(const string & text)
{
	m_text = text;
}


CImage::CImage(Path & path)
	: m_path(path)
{}

Path CImage::GetPath() const
{
	return Path();
}

int CImage::GetWidth() const
{
	return 0;
}

int CImage::GetHeight() const
{
	return 0;
}

void CImage::Resize(int width, int height)
{}
