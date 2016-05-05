// ISpringWord.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Menu.h"
#include "Document.h"

using namespace std;
using namespace std::placeholders;

namespace
{

class CEditor
{
public:
	CEditor()  //-V730
		:m_document(make_unique<CDocument>())
	{
		m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
		m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
		m_menu.AddItem("setTitle", "Changes title. Args: <new title>", bind(&CEditor::SetTitle, this, _1));
		m_menu.AddItem("list", "Show document", bind(&CEditor::List, this, _1));
	}

	void Start()
	{
		m_menu.Run();
	}

private:

	// TODO: скипнуть первый пробел элегантнее
	void SetTitle(istream & in)
	{
		string head;
		string tail;

		if (in >> head)
		{
			getline(in, tail);
		}
		string title = head + tail;

		m_document->SetTitle(title);
	}

	void List(istream &)
	{
		cout << "-------------" << endl;
		cout << m_document->GetTitle() << endl;
		cout << "-------------" << endl;
	}

	CMenu m_menu;
	unique_ptr<IDocument> m_document;
};

}

int main()
{
	CEditor editor;
	editor.Start();
    return 0;
}

