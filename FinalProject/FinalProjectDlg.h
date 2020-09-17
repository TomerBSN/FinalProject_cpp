
// FinalProjectDlg.h : header file
//

#pragma once
#include "afxdialogex.h"
#include "Person.h"
#include <vector>
#include <list>
using namespace std;
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
	int callfromSearch = 0;

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
	void ClearFieldsOnScreen();
	void ToggleVisibilty(bool visiblity, int group);
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
	afx_msg void OnBnClickedbtnsaveall();
	void fillCstringList(CString wholeFile);
	vector <CString> seperateLine(CString theLine, CString seperator);
	CString loadFile(TCHAR* FileName);
	bool checkUserInputData(int selectedFormType);
	bool CheckDate(Date d1, Date d2);
	afx_msg void OnBnClickedbtnsavedetails();
	CDateTimeCtrl dtpPositiveTestController;
	CDateTimeCtrl dtpHospitalEntryController;
	CDateTimeCtrl dtpIsolationEntryController;
	CDateTimeCtrl dtpRecoveryDateController;
	CButton comboSearchController;
};
