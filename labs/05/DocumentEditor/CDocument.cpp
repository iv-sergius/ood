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
