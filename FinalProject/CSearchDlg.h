#pragma once
#include "FinalProjectDlg.h"
#include "afxdialogex.h"
// CSearchDlg dialog

class CSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSearchDlg)

public:
	CSearchDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSearchDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCH_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP();
public:
	afx_msg void OnBnClickedbtnSearchSh();
	afx_msg void OnCbnSelchangecombosearchopt();
	afx_msg void OnBnProceedClickedSh();
	CComboBox comboSearchOptController;
	CComboBox comboSearchStatController;
	CButton comboSearchController;
};
