#pragma once

#include "ICommand_fwd.h"

class CHistory
{
public:
	CHistory();
	~CHistory();

	bool CanUndo()const;
	void Undo();
	void AddAndExecuteCommand(ICommandPtr && command);
private:
	ICommandPtr m_currentCommand;
};

