#include "stdafx.h"
#include "Document.h"

void CDocument::SetTitle(const std::string & title)
{
	m_title = title;
}

std::string CDocument::GetTitle() const
{
	return m_title;
}
