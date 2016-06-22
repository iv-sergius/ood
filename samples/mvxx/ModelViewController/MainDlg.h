
// MainDlg.h : header file
//
#pragma once

#include "Signals.h"

class CEquationSolver;
class IMainDlgController;

class CMainDlg : public CDialogEx
{
public:
	CMainDlg(CEquationSolver & solver, IMainDlgController & controller, CWnd* pParent = NULL);	// standard constructor

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODELVIEWCONTROLLER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
private:
	void SetSolutionText(const std::wstring & text);
	void UpdateSolution();
	afx_msg void OnChangeCoeffA();
	afx_msg void OnChangeCoeffB();
	afx_msg void OnChangeCoeffC();
	afx_msg void OnDestroy();


	sig::scoped_connection m_solutionChangeConnection;
	IMainDlgController & m_controller;
	CEquationSolver & m_solver;
	double m_coeffA = 0;
	double m_coeffB = 0;
	double m_coeffC = 0;

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
