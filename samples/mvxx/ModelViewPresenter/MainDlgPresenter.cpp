#include "stdafx.h"
#include "MainDlgPresenter.h"
#include "IMainDlgView.h"
#include "EquationSolver.h"

CMainDlgPresenter::CMainDlgPresenter(CEquationSolver & solver, IMainDlgView & view)
	: m_solver(solver)
	, m_view(view)
{
	m_view.DoOnCoeffAChange(std::bind(&CEquationSolver::SetQuadraticCoeff, &m_solver, std::placeholders::_1));
	m_view.DoOnCoeffBChange(std::bind(&CEquationSolver::SetLinearCoeff, &m_solver, std::placeholders::_1));
	m_view.DoOnCoeffCChange(std::bind(&CEquationSolver::SetConstantCoeff, &m_solver, std::placeholders::_1));
	m_view.DoOnInit(std::bind(&CMainDlgPresenter::InitView, this));
	m_solver.DoOnSolutionChange(std::bind(&CMainDlgPresenter::UpdateSolution, this));
}

void CMainDlgPresenter::Run()
{
	m_view.Show();
}

void CMainDlgPresenter::InitView()
{
	m_view.SetCoeffs(m_solver.GetQuadraticCoeff(), m_solver.GetLinearCoeff(), m_solver.GetConstantCoeff());
	UpdateSolution();
}

void CMainDlgPresenter::UpdateSolution()
{
	struct SolutionPrinter : boost::static_visitor<void>
	{
		IMainDlgView & view;
		SolutionPrinter(IMainDlgView & view)
			:view(view)
		{
		}
		void operator()(NoRealRoots)
		{
			view.SetNoSolution();
		}
		void operator()(InfiniteNumberOfRoots)
		{
			view.SetInfiniteSolutions();
		}
		void operator()(double root)
		{
			view.SetSingleSolution(root);
		}
		void operator()(const std::pair<double, double> & roots)
		{
			view.SetTwoRootsSolutuion(roots.first, roots.second);
		}
	};

	SolutionPrinter printer(m_view);
	m_solver.GetEquationRoots().apply_visitor(printer);
}

