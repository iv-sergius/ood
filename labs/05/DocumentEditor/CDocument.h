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
	// Возвращает путь относительно каталога документа
	Path GetPath() const;

	// Ширина изображения в пикселях
	int GetWidth() const;
	// Высота изображения в пикселях
	int GetHeight() const;

	// Изменяет размер изображения
	void Resize(int width, int height);
private:
	Path m_path;
};

class CDocument : public IDocument
{

};