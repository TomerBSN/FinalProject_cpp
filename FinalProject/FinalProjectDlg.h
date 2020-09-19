// FinalProjectDlg.h : header file

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
	// Event-driven methods
	afx_msg void OnBnClickedbtnsearch();
	afx_msg void OnBnClickedbtncreategraphs();
	afx_msg void OnBnClickedbtnabout();
	afx_msg void OnBnClickedbtncreate();
	afx_msg void OnBnClickedbtnclearall();
	afx_msg void OnBnClickedbtnaddperson();
	afx_msg void OnBnClickedbtnsaveall();
	afx_msg void OnBnClickedbtnsavedetails();
	afx_msg void OnDestroy();

	// Utility methods
	void ClearFieldsOnScreen();
	void ToggleVisibilty(bool visiblity, int group);
	void savePersonsToFile();
	void fillCstringList(CString wholeFile);
	void Clear_InvalidIsolated();
	void ValidateUserInput(CComboBox& Controller, bool& isCorrect);
	bool checkUserInputData(int selectedFormType);
	vector <CString> seperateLine(CString theLine, CString seperator);
	CString loadFile(TCHAR* FileName);
	template <class T> void SetBorderColor(T &Controller, int R, int G, int B);
	template <class T> void ValidateUserInput(T& Controller, bool& isCorrect, CString Item1 = _T(""), CString Item2 = _T(""));

	// Controllers
	CComboBox comboDataTypeController;
	CComboBox comboGenderController;
	CComboBox comboInfectionAreaTypeController;
	CComboBox comboIsolationCityController;
	CComboBox comboHospitalController;
	CComboBox comboSicknessLevelController;
	CComboBox comboVentilatedController;
	CComboBox comboCityController;
	CDateTimeCtrl dtpBirthDateController;
	CDateTimeCtrl dtpPositiveTestController;
	CDateTimeCtrl dtpHospitalEntryController;
	CDateTimeCtrl dtpIsolationEntryController;
	CDateTimeCtrl dtpRecoveryDateController;
	CButton comboSearchController;
	CEdit txtIDController;
	CEdit txtFullNameController;
	CEdit txtAddressController;
	CEdit txtIsolationAddressController;
	CEdit txtExposedIDController;
	CEdit txtInfectorIDController;
};
