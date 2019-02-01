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
public:
	CImage(Path & path);
	// ���������� ���� ������������ �������� ���������
	Path GetPath() const;

	// ������ ����������� � ��������
	int GetWidth() const;
	// ������ ����������� � ��������
	int GetHeight() const;

	// �������� ������ �����������
	void Resize(int width, int height);
private:
	Path m_path;
};

class CDocument : public IDocument
{

};