#include "Menu.h"
#include "MenuFP.h"
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

class CExitMenuCommand : public ICommand
{
public:
	CExitMenuCommand(CMenu & menu)
		:m_menu(menu)
	{}

	void Execute() override
	{
		m_menu.Exit();
	}
private:
	CMenu & m_menu;
};

void TestMenuWithClassicCommandPattern()
{
	CRobot robot;
	CMenu menu;
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

	menu.AddItem("help", "Show instructions",
		make_unique<CMenuHelpCommand>(menu));
	menu.AddItem("exit", "Exit from this menu",
		make_unique<CExitMenuCommand>(menu));

	menu.ShowInstructions();

	menu.Run();
}

void TestMenuWithFunctionalCommandPattern()
{
	CRobot robot;
	CMenuFP menu;
	menu.AddItem("on", "Turns the Robot on", [&] { 
		robot.TurnOn(); 
	});
	menu.AddItem("off", "Turns the Robot off",
		bind(&CRobot::TurnOff, &robot));

	menu.AddItem("north", "Makes the Robot walk north", 
		bind(&CRobot::Walk, &robot, WalkDirection::North));
	menu.AddItem("south", "Makes the Robot walk south", 
		bind(&CRobot::Walk, &robot, WalkDirection::South));
	menu.AddItem("west", "Makes the Robot walk west", 
		bind(&CRobot::Walk, &robot, WalkDirection::West));
	menu.AddItem("east", "Makes the Robot walk east", 
		bind(&CRobot::Walk, &robot, WalkDirection::East));

	menu.AddItem("stop", "Stops the Robot", 
		bind(&CRobot::Stop, &robot));

	menu.AddItem("help", "Show instructions", 
		bind(&CMenuFP::ShowInstructions, &menu));
	menu.AddItem("exit", "Exit from this menu", 
		bind(&CMenuFP::Exit, &menu));

	menu.ShowInstructions();

	menu.Run();
}

int main()
{
	CMenuFP menu;
	menu.AddItem("c", "Classic command pattern implementation", [&] {
		TestMenuWithClassicCommandPattern(); 
		menu.ShowInstructions();
	});
	menu.AddItem("f", "Functional command pattern implementation", [&] {
		TestMenuWithClassicCommandPattern(); 
		menu.ShowInstructions();
	});

	menu.AddItem("q", "Exit Program", bind(&CMenuFP::Exit, &menu));
	menu.ShowInstructions();
	menu.Run();
	
	return 0;
}