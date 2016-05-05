#pragma once
#include "IDocument.h"

class CDocument:public IDocument
{
public:

	void SetTitle(const std::string & title) override;

	std::string GetTitle() const override;

private:
	std::string m_title;

};