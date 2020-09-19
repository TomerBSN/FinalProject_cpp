// CSearchDlg.cpp : implementation file
//

//#include "pch.h"
#include "FinalProject.h"
#include "CSearchDlg.h"
#include "afxdialogex.h"
#include "Global.h"

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
	DDX_Control(pDX, comboSearchOpt, comboSearchOptController);
	DDX_Control(pDX, comboSearchStat, comboSearchStatController);
	DDX_Control(pDX, btnSearchID_SH, comboSearchController);
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialogEx)
	ON_BN_CLICKED(btnSearchID_SH, &CSearchDlg::OnBnClickedbtnSearchSh)
	ON_CBN_SELCHANGE(comboSearchOpt, &CSearchDlg::OnCbnSelchangecombosearchopt)
	ON_BN_CLICKED(btnSearchProceed_SH, &CSearchDlg::OnBnProceedClickedSh)
END_MESSAGE_MAP()


// CSearchDlg message handlers


/*
Function: [Event-Driven] After the button is clicked, the function loops through ther List of Person's and cross checks the ID, if found the other fields will be shown then the fields will be filled with information as per the information dedicated into that object. If there is no such person, a error will be shown.
*/
void CSearchDlg::OnBnClickedbtnSearchSh()
{
	// TODO: Add the actual search code here.
	CString ID;
	GetDlgItemText(txtSearchID_SH, ID);
	bool found = searchPersonByID(ID);
	
	if (found)
	{
		comboSearchController.EnableWindow(false);
		GetDlgItem(btnSearchProceed_SH)->EnableWindow(true);
		comboSearchOptController.EnableWindow(true);
	}
	else	//ERROR IN FINDING THIS PERSON
		MessageBox(_T("Person not found!"));
}

/*
Function: [Event-Driven] if user has changed the options combobox selection, we want to check if he selected update details
*/
void CSearchDlg::OnCbnSelchangecombosearchopt()
{
	if (comboSearchOptController.GetCurSel() == 0)       // update status selection
	{
		comboSearchStatController.EnableWindow(true);    // enable status combobox
		comboSearchStatController.SetCurSel(Persons[searchPersonID]->get_itemType());
	}
	else
		comboSearchStatController.EnableWindow(false);
}

/*
Function: [Event-Driven] user clicked proceed button
*/
void CSearchDlg::OnBnProceedClickedSh()
{
	int selectedNum = comboSearchOptController.GetCurSel();
	
	switch (selectedNum)
	{
		case 0:       // Update status
		{
			EndDialog(comboSearchStatController.GetCurSel() + 5);        // dialog returns the itemtype + 5 (random value)
			break;
		}

		case 1:       // Edit details
		{
			EndDialog(Persons[searchPersonID]->get_itemType() + 5);		 // dialog returns the itemtype + 5 (random value)
			break;
		}

		case 2:       // Delete person
		{
			updateCounters(Persons[searchPersonID], false);				// decrease all relevant counters in 1
			Persons.erase(Persons.begin() + searchPersonID);			// remove person from Persons vector
			EndDialog(0);
			MessageBox(_T("Person deleted!"));
			break;
		}

		default:
			break;
	}
}
