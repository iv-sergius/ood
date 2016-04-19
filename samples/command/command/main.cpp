#include "Menu.h"
#include "Commands.h"
	
using namespace std;

class CMenuHelpCommand : public ICommand
{
public:
	CMenuHelpCommand(const CMenu & menu)
		:m_menu(menu)
	{}

	void Execute() override
	{
		m_menu.ShowInstructions();
	}
private:
	const CMenu & m_menu;
};

int main()
{
	CRobot robot;
	CMenu menu;
	menu.AddItem("help", "Show instructions", 
		make_unique<CMenuHelpCommand>(menu));

	menu.AddItem("on", "Turns the Robot on", 
		make_unique<CTurnOnCommand>(robot));
	menu.AddItem("off", "Turns the Robot off", 
		make_unique<CTurnOffCommand>(robot));

	menu.AddItem("north", "Makes the Robot walk north", 
		make_unique<CWalkCommand>(robot, WalkDirection::North));
	menu.AddItem("south", "Makes the Robot walk south",
		make_unique<CWalkCommand>(robot, WalkDirection::South));
	menu.AddItem("west", "Makes the Robot walk west",
		make_unique<CWalkCommand>(robot, WalkDirection::West));
	menu.AddItem("east", "Makes the Robot walk east",
		make_unique<CWalkCommand>(robot, WalkDirection::East));

	menu.AddItem("stop", "Stops the Robot",
		make_unique<CStopCommand>(robot));

	menu.ShowInstructions();
	string command;
	while (getline(cin, command))
	{
		menu.ExecuteCommand(command);
	}

	return 0;
}