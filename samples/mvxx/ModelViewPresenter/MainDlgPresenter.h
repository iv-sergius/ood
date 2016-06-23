#pragma once


class CEquationSolver;
class IMainDlgView;

class CMainDlgPresenter
{
public:
	CMainDlgPresenter(CEquationSolver & solver, IMainDlgView & view);
	void Run();
private:
	void InitView();
	void UpdateSolution();
	CEquationSolver & m_solver;
	IMainDlgView & m_view;
};

