#pragma once

extern "C" __declspec(dllimport) double Ex20cSquareRoot(double d);
// CTest20cDialog dialog

class CTest20cDialog : public CDialog
{
	DECLARE_DYNAMIC(CTest20cDialog)

public:
	CTest20cDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTest20cDialog();

// Dialog Data
	enum { IDD = IDD_EX20C };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCompute();
	double m_dInput;
	double m_dOutput;
};
