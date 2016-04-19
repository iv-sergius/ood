#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <boost/range/algorithm/find_if.hpp>

#include "ICommand.h"


class CMenu
{
public:
	void AddItem(
		const std::string & shortcut,
		const std::string & description,
		std::unique_ptr<ICommand> && command)
	{
		m_items.emplace_back(shortcut, description, std::move(command));
	}

	void ExecuteCommand(const std::string & command)
	{
		auto it = boost::find_if(m_items, [&](const Item & item) {
			return item.shortcut == command;
		});
		if (it != m_items.end())
		{
			it->command->Execute();
		}
		else
		{
			std::cout << "Unknown command\n";
		}
	}

	void ShowInstructions()const
	{
		std::cout << "Commands list:\n";
		for (auto & item : m_items)
		{
			std::cout << item.shortcut << ": " << item.description << "\n";
		}
	}
private:
	struct Item
	{
		Item(const std::string & shortcut, const std::string & description, std::unique_ptr<ICommand> && command)
			: shortcut(shortcut)
			, description(description)
			, command(std::move(command))
		{}

		std::string shortcut;
		std::string description;
		std::unique_ptr<ICommand> command;
	};
	std::vector<Item> m_items;
};