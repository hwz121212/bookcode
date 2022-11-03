// CommandManager.h: interface for the CCommandManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMANDMANAGER_H__DC176E89_5388_4701_A9A9_3182E92796FD__INCLUDED_)
#define AFX_COMMANDMANAGER_H__DC176E89_5388_4701_A9A9_3182E92796FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ICommand.h"

class CCommandManager  
{
	stack<CICommand*> m_undolist;
	stack<CICommand*> m_redolist;
public:
	CCommandManager()
	{

	}
	virtual ~CCommandManager()
	{

	}

	BOOL CanRedo() const
	{
		return (m_redolist.size() > 0);
	}

	BOOL CanUndo() const
	{
		return (m_undolist.size() > 0);
	}

	void DoCommand(CICommand* pCommand)
	{
		ASSERT(pCommand);
		pCommand->Execute();
		m_undolist.push(pCommand);
	}

	void Undo()
	{
		if (!CanUndo())
			return;
		CICommand* pCommand = m_undolist.top();
		pCommand->Unexecute();
		m_redolist.push(pCommand);
		m_undolist.pop();
	}

	void Redo()
	{
		if (!CanRedo())
			return;
		CICommand* pCommand = m_redolist.top();
		pCommand->Execute();
		m_undolist.push(pCommand);
		m_redolist.pop();
	}

};

#endif // !defined(AFX_COMMANDMANAGER_H__DC176E89_5388_4701_A9A9_3182E92796FD__INCLUDED_)
