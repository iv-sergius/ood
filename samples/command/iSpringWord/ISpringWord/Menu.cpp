#include "stdafx.h"
#include "Menu.h"

inline void CMenu::AddItem(const std::string & shortcut, const std::string & description, const Command & command)
{
	m_items.emplace_back(shortcut, description, command);
}

inline void CMenu::Run()
{
	ShowInstructions();

	std::string command;
	while ((std::cout << ">")
		&& getline(std::cin, command)
		&& ExecuteCommand(command))
	{
	}
}

inline void CMenu::ShowInstructions() const
{
	std::cout << "Commands list:\n";
	for (auto & item : m_items)
	{
		std::cout << "  " << item.shortcut << ": " << item.description << "\n";
	}
}

inline void CMenu::Exit()
{
	m_exit = true;
}

inline bool CMenu::ExecuteCommand(const std::string & command)
{
	m_exit = false;
	auto it = boost::find_if(m_items, [&](const Item & item) {
		return item.shortcut == command;
	});
	if (it != m_items.end())
	{
		it->command();
	}
	else
	{
		std::cout << "Unknown command\n";
	}
	return !m_exit;
}
