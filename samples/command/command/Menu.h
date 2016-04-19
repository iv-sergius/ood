#pragma once
#include <vector>
#include <string>
#include <memory>

#include "ICommand.h"


class CMenu
{
public:
	void AddItem(const std::string & description,
		std::unique_ptr<ICommand> && command)
	{
		m_items.emplace_back(description, std::move(command));
	}
private:
	struct Item
	{
		Item(const std::string & description, std::unique_ptr<ICommand> && command)
			: description(description)
			, command(std::move(command))
		{
		}

		std::string description;
		std::unique_ptr<ICommand> command;
	};
	std::vector<Item> m_items;
};