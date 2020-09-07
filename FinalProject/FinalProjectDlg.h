
// FinalProjectDlg.h : header file
//

#pragma once
#include "afxdialogex.h"
#include "Person.h"
#include <vector>
// CFinalProjectDlg dialog
class CFinalProjectDlg : public CDialogEx
{
// Construction
public:
	CFinalProjectDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FINALPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedbtnsearch();
	afx_msg void OnBnClickedbtncreategraphs();
	afx_msg void OnBnClickedbtnabout();
	afx_msg void OnBnClickedbtncreate();
	
	afx_msg void OnBnClickedbtnclearall();
	void ToggleVisibilty(bool visiblity, int group);
	Person person;
	vector <Person*> Persons;
	CComboBox comboDataTypeController;
	CComboBox comboGenderController;
	CComboBox comboStatusController;
	CComboBox comboInfectionAreaTypeController;
	CComboBox comboIsolationCityController;
	CComboBox comboHospitalController;
	CComboBox comboSicknessLevelController;
	CComboBox comboVentilatedController;
	CComboBox comboCityController;
	CDateTimeCtrl dtpBirthDateController;
	afx_msg void OnBnClickedbtnaddperson();
};
