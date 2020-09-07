// CSearchDlg.cpp : implementation file
//

//#include "pch.h"
#include "FinalProject.h"
#include "CSearchDlg.h"
#include "afxdialogex.h"


// CSearchDlg dialog

IMPLEMENT_DYNAMIC(CSearchDlg, CDialogEx)

CSearchDlg::CSearchDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEARCH_DIALOG, pParent)
{

}

CSearchDlg::~CSearchDlg()
{
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialogEx)
	ON_BN_CLICKED(btnSearchID_SH, &CSearchDlg::OnBnClickedbtnSearchSh)
END_MESSAGE_MAP()


// CSearchDlg message handlers


/*
Function: [Event-Driven] After the button is clicked, the function loops through ther List of Person's and cross checks the ID, if found the other fields will be shown then the fields will be filled with information as per the information dedicated into that object. If there is no such person, a error will be shown. 
*/
void CSearchDlg::OnBnClickedbtnSearchSh()
{
	// TODO: Add the actual search code here.
	bool found = true;

	if (found == false)
	{
		//ERROR IN FINDING THIS PERSON
		GetDlgItem(staError_SH)->ShowWindow(SW_SHOW);
	}
	else {
		//to be edited as per the info we will get in the type of it, though idk, maybe we should showcase it all.
		for (int i = 1; i <= 3; i++) ToggleVisibilty(true, i);
		//TODO: Showcase the information into the places already.
	}
}


void CSearchDlg::ToggleVisibilty(bool visiblity, int chunk)
{
	GetDlgItem(staDataType_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
	GetDlgItem(comboDataType_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);

	switch (chunk)
	{
		case 1://chunk 1 - left fields
		{
			GetDlgItem(staAddress_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(txtAddress_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(txtID_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staID_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(txtFullName_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staFullName_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(dtpBirthdate_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staBirthdate_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboGender_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staGender_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboCity_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staCity_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staStatus_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboStatus_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			break;
		}
		case 2://chunk 2 - middle fields
		{
			GetDlgItem(staInfectorID_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(txtInfectorID_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboInfectionArea_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staInfectionArea_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(dtpPositiveTest_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staPositiveTest_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(dtpRecoveryDate_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staRecoveryDate_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboIsolationAddress_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staIsolationAddress_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboIsolationCity_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staIsolationCity_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			break;
		}
		case 3://chunk 3 - right fields
		{
			GetDlgItem(staHospitalDate_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(dtpHospitalDate_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staVentilated_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboVentilated_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staHospitalName_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboHospitalName_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboSicknessLevel_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staSicknessLevel_SH)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			break;
		}
	}
}