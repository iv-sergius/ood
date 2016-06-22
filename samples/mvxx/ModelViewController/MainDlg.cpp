
// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MVCApp.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "EquationSolver.h"
#include "IMainDlgController.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMainDlg::CMainDlg(CEquationSolver & solver, IMainDlgController & controller, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MODELVIEWCONTROLLER_DIALOG, pParent)
	, m_controller(controller)
	, m_solver(solver)
	, m_coeffA(solver.GetQuadraticCoeff())
	, m_coeffB(solver.GetLinearCoeff())
	, m_coeffC(solver.GetConstantCoeff())
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COEFF_A, m_coeffA);
	DDX_Text(pDX, IDC_COEFF_B, m_coeffB);
	DDX_Text(pDX, IDC_COEFF_C, m_coeffC);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_EN_UPDATE(IDC_COEFF_A, &CMainDlg::OnChangeCoeffA)
	ON_EN_CHANGE(IDC_COEFF_B, &CMainDlg::OnChangeCoeffB)
	ON_EN_CHANGE(IDC_COEFF_C, &CMainDlg::OnChangeCoeffC)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_solutionChangeConnection = m_solver.DoOnSolutionChange([=] {
		UpdateSolution();
	});

	UpdateSolution();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainDlg::SetSolutionText(const std::wstring & text)
{
	CDataExchange dx(this, false);
	SetDlgItemText(IDC_SOLUTION, text.c_str());
}

void CMainDlg::UpdateSolution()
{
	auto solution = m_solver.GetEquationRoots();
	struct SolutionPrinter : boost::static_visitor<void>
	{
		CMainDlg & self;
		SolutionPrinter(CMainDlg &self)
			:self(self)
		{
		}
		void operator()(NoRealRoots)
		{
			self.SetSolutionText(L"No real roots");
		}
		void operator()(InfiniteNumberOfRoots)
		{
			self.SetSolutionText(L"Infinite number of roots");
		}
		void operator()(double root)
		{
			self.SetSolutionText((boost::wformat(L"One root: %1%") % root).str());
		}
		void operator()(const std::pair<double, double> & roots)
		{
			self.SetSolutionText((boost::wformat(L"Two roots: %1% and %2%") % roots.first % roots.second).str());
		}
	};

	SolutionPrinter printer(*this);
	solution.apply_visitor(printer);
}

void CMainDlg::OnChangeCoeffA()
{
	UpdateData();
	m_controller.SetCoeffA(m_coeffA);
}

void CMainDlg::OnChangeCoeffB()
{
	UpdateData();
	m_controller.SetCoeffB(m_coeffB);
}

void CMainDlg::OnChangeCoeffC()
{
	UpdateData();
	m_controller.SetCoeffC(m_coeffC);
}


void CMainDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}
