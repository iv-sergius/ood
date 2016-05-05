#include "stdafx.h"
#include "History.h"
#include "ICommand.h"

CHistory::CHistory()
{
}


CHistory::~CHistory()
{
}

bool CHistory::CanUndo() const
{
	return m_currentCommand != nullptr;
}

void CHistory::Undo()
{
	if (CanUndo())
	{
		m_currentCommand->Unexecute();
		m_currentCommand.reset();
	}
}

void CHistory::AddAndExecuteCommand(ICommandPtr && command)
{
	command->Execute();
	m_currentCommand = move(command);
}
