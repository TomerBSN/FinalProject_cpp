#define _CRT_SECURE_NO_WARNINGS
// FinalProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FinalProject.h"
#include "FinalProjectDlg.h"
#include "afxdialogex.h"
#include "CGraphDlg.h"
#include "CSearchDlg.h"
#include <string>
#include "Hospitalized.h"
#include "NonHospitalized.h"
#include "Recovered.h"
#include "Isolated.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFinalProjectDlg dialog



CFinalProjectDlg::CFinalProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FINALPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFinalProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//combobox controllers
	DDX_Control(pDX, comboDataType, comboDataTypeController);
	DDX_Control(pDX, comboGender, comboGenderController);
	DDX_Control(pDX, comboStatus, comboStatusController);
	DDX_Control(pDX, comboInfectionAreaType, comboInfectionAreaTypeController);
	DDX_Control(pDX, comboIsolationCity, comboIsolationCityController);
	DDX_Control(pDX, comboHospital, comboHospitalController);
	DDX_Control(pDX, comboSicknessLevel, comboSicknessLevelController);
	DDX_Control(pDX, comboVentilated, comboVentilatedController);
	DDX_Control(pDX, comboCity, comboCityController);
	DDX_Control(pDX, dtpBirthDate, dtpBirthDateController);
}

BEGIN_MESSAGE_MAP(CFinalProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(btnSearch, &CFinalProjectDlg::OnBnClickedbtnsearch)
	ON_BN_CLICKED(btnCreateGraphs, &CFinalProjectDlg::OnBnClickedbtncreategraphs)
	ON_BN_CLICKED(btnAbout, &CFinalProjectDlg::OnBnClickedbtnabout)
	ON_BN_CLICKED(btnCreate, &CFinalProjectDlg::OnBnClickedbtncreate)
	ON_BN_CLICKED(btnClearAll, &CFinalProjectDlg::OnBnClickedbtnclearall)
	ON_BN_CLICKED(btnAddPerson, &CFinalProjectDlg::OnBnClickedbtnaddperson)
	ON_BN_CLICKED(btnSaveAll, &CFinalProjectDlg::OnBnClickedbtnsaveall)
END_MESSAGE_MAP()


// CFinalProjectDlg message handlers

BOOL CFinalProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Comboboxes initialization
	for (int i = 0; i < NUM_OF_CITYS; i++) {
		comboCityController.InsertString(i, CString(Citys[i].c_str()));
		comboIsolationCityController.InsertString(i, CString(Citys[i].c_str()));
	}
	for (int i = 0; i < NUM_OF_HOSPITALS; i++)
		comboHospitalController.InsertString(i, CString(Hospitals[i].c_str()));
	for (int i = 0; i < NUM_OF_INFECTIONAREAS; i++)
		comboInfectionAreaTypeController.InsertString(i, CString(InfectionAreas[i].c_str()));
	
	comboDataTypeController.SetCurSel(0); //percaution so the user does not create a incorrect type of person into this field.
	//To add: Load the persons vector from the personsSave.txt file properly.
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFinalProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFinalProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFinalProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*
Function: [Event-Driven] Will bring up the IDD_SEARCH_DIALOG.
*/
void CFinalProjectDlg::OnBnClickedbtnsearch()
{
	CSearchDlg search;
	search.DoModal();
}

/*
Function: [Event-Driven] Will bring up the IDD_GRAPH_DIALOG.
*/
void CFinalProjectDlg::OnBnClickedbtncreategraphs()
{
	CGraphDlg gra;
	gra.DoModal();
}

/*
Function: [Event-Driven] Will bring up the IDD_ABOUTBOX.
*/
void CFinalProjectDlg::OnBnClickedbtnabout()
{
	CAboutDlg ab;
	ab.DoModal();
}

/*
Function: [Event-Driven] Will reveal all the corresponding fields within the IDD_FINALPROJECT_DIALOG.
*/
void CFinalProjectDlg::OnBnClickedbtncreate()
{
	CString str;
	GetDlgItem(staAddPerson)->ShowWindow(SW_HIDE);
	ToggleVisibilty(true, 1);
	
	switch (comboDataTypeController.GetCurSel())//Hospitalized;Not Hospitalized;Recovered;Self Isolation;
	{
		case 0://Hospitalized
		{
			ToggleVisibilty(true, 2);
			ToggleVisibilty(true, 4);
			break;
		}
		case 1://Not Hospitalized
		{
			ToggleVisibilty(true, 3);
			ToggleVisibilty(true, 2);
			break;
		}
		case 2://Recovered
		{
			ToggleVisibilty(true, 2);
			ToggleVisibilty(true, 5);
			break;
		}
		case 3://Self Isolation
		{
			ToggleVisibilty(true, 3);
			break;
		}
		default:
		{
			break;
		}
	}
	GetDlgItem(btnCreate)->EnableWindow(false);
	comboDataTypeController.EnableWindow(false);
}

/*
Function: [Event-Driven] When clicking the button it will reset the window to its clear position without any oddities.
*/
void CFinalProjectDlg::OnBnClickedbtnclearall()
{
	// TODO: clear the text and all that shit.
	ClearFieldsOnScreen();
	GetDlgItem(staAddPerson)->ShowWindow(SW_HIDE);

}
void CFinalProjectDlg::ClearFieldsOnScreen()
{
	CString cs;
	cs.Format(_T(""));
	SetDlgItemText(txtID, cs);
	SetDlgItemText(txtAddress, cs);
	SetDlgItemText(txtFullName, cs);
	SetDlgItemText(txtInfectorID, cs);
	SetDlgItemText(txtIsolationAddress, cs);
	comboDataTypeController.SetCurSel(0);//always put it as 0, -1 can cause user generated issues.
	comboGenderController.SetCurSel(-1);
	comboHospitalController.SetCurSel(-1);
	comboInfectionAreaTypeController.SetCurSel(-1);
	comboIsolationCityController.SetCurSel(-1);
	comboSicknessLevelController.SetCurSel(-1);
	comboStatusController.SetCurSel(-1);
	comboVentilatedController.SetCurSel(-1);
	comboCityController.SetCurSel(-1);

	for (int i = 1; i <= 5; i++) ToggleVisibilty(false, i);
	GetDlgItem(btnCreate)->EnableWindow(true);
	comboDataTypeController.EnableWindow(true);
}
/*
Function: [void] will toggle the ShowWindow of each DlgItem depending on their "chunk"/group affiliation.
		Visibilty: True = Show, False = Hide
		chunk: 1 - Top Row, 2 - first line second row, 3 - isolated row, 4 - hospital, 5 - recovered
*/
void CFinalProjectDlg::ToggleVisibilty(bool visiblity, int chunk)
{
	
	switch (chunk)
	{
		case 1://chunk 1 - top rank
		{
			GetDlgItem(staHeader1)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE); //SW_HIDE
			GetDlgItem(staID)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(txtID)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staName)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(txtFullName)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staBirthdate)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(dtpBirthDate)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staGender)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboGender)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staCity)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboCity)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staAddress)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(txtAddress)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staStatus)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboStatus)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			break;
		}
		case 2://chunk 2 - all* second tier
		{	
			GetDlgItem(staHeader2)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staPosTest)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(dtpPositiveTest)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staIDInfector)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(txtInfectorID)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staAreaType)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboInfectionAreaType)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staExposedID)->ShowWindow(visiblity ? SW_HIDE : SW_SHOW);//	
			GetDlgItem(txtExposedID)->ShowWindow(visiblity ? SW_HIDE : SW_SHOW);//
			GetDlgItem(staIsolationEntry)->ShowWindow(visiblity ? SW_HIDE : SW_SHOW);
			GetDlgItem(dtpIsolationEntry)->ShowWindow(visiblity ? SW_HIDE : SW_SHOW);
			break;
		}
		case 3://chunk 3 - isolated
		{
			GetDlgItem(staHeader2)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staIsolatedCity)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboIsolationCity)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staIsolatedAddress)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);//
			GetDlgItem(txtIsolationAddress)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);//
			GetDlgItem(staExposedID)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);//	
			GetDlgItem(txtExposedID)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);//
			GetDlgItem(staIsolationEntry)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(dtpIsolationEntry)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			break;
		}
		case 4://chunk 4 - hospital
		{
			GetDlgItem(staHeader2)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staHospitalName)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboHospital)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staSicknessLevel)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboSicknessLevel)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staVentilated)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboVentilated)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staHospitalDate)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(dtpHospitalEntry)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			break;
		}
		case 5://chunk 5 - recovered
		{
			GetDlgItem(staHeader2)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staRecoveryDate)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(dtpRecoveryDate)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			break;
		}
	}
}

/*
Function: [Event-Driven] On click the data filled in the fields will be placed into a Person type object.
*/
void CFinalProjectDlg::OnBnClickedbtnaddperson()
{
	Person* NewPerson;
	bool Gender, IsVentilated;
	Address Addr, IsolationAddr;
	Date Birthday, PositiveTest, HospitalEntry, Recovery, IsolationEntry;
	CString ID, Name, DateBuffer, InfectedBy, ExposedTo, Hospital, Level, Area;
	int selectedForm = comboDataTypeController.GetCurSel();
	Gender = comboGenderController.GetCurSel();
	GetDlgItemText(txtID, ID);
	GetDlgItemText(txtFullName, Name);
	GetDlgItemText(txtAddress, Addr.street);
	comboCityController.GetLBText(comboCityController.GetCurSel(), Addr.city);
	GetDlgItemText(dtpBirthDate, DateBuffer);
	Birthday.day = _ttoi(DateBuffer.Mid(0, 2));
	Birthday.month = _ttoi(DateBuffer.Mid(3, 5));
	Birthday.year = _ttoi(DateBuffer.Mid(6, 10));

	if (selectedForm<=2)
	{ 
		GetDlgItemText(dtpPositiveTest, DateBuffer);
		PositiveTest.day = _ttoi(DateBuffer.Mid(0, 2));
		PositiveTest.month = _ttoi(DateBuffer.Mid(3, 5));
		PositiveTest.year = _ttoi(DateBuffer.Mid(6, 10));
		GetDlgItemText(txtInfectorID, InfectedBy); 
		comboSicknessLevelController.GetLBText(comboInfectionAreaTypeController.GetCurSel(), Area);

		switch (comboDataTypeController.GetCurSel())//Hospitalized;Not Hospitalized;Recovered;Self Isolation;
		{
			case 0:	//Hospitalized
			{
				comboHospitalController.GetLBText(comboHospitalController.GetCurSel(), Hospital);
				comboSicknessLevelController.GetLBText(comboSicknessLevelController.GetCurSel(), Level);
				IsVentilated = comboVentilatedController.GetCurSel();
				GetDlgItemText(dtpHospitalEntry, DateBuffer);
				HospitalEntry.day = _ttoi(DateBuffer.Mid(0, 2));
				HospitalEntry.month = _ttoi(DateBuffer.Mid(3, 5));
				HospitalEntry.year = _ttoi(DateBuffer.Mid(6, 10));
				NewPerson = new Hospitalized(Gender, ID, Name, Addr, Birthday,
					PositiveTest, Area, InfectedBy, Level, IsVentilated, Hospital, HospitalEntry);
				break;
			}
			case 1:	//Not Hospitalized
			{
				GetDlgItemText(txtIsolationAddress, IsolationAddr.street);
				comboIsolationCityController.GetLBText(comboIsolationCityController.GetCurSel(), IsolationAddr.city);
				NewPerson = new NonHospitalized(Gender, ID, Name, Addr, Birthday,
					PositiveTest, Area, InfectedBy, IsolationAddr);
				break;
			}
			case 2: //Recovered
			{
				GetDlgItemText(dtpRecoveryDate, DateBuffer);
				Recovery.day = _ttoi(DateBuffer.Mid(0, 2));
				Recovery.month = _ttoi(DateBuffer.Mid(3, 5));
				Recovery.year = _ttoi(DateBuffer.Mid(6, 10));
				NewPerson = new Recovered(Gender, ID, Name, Addr, Birthday, PositiveTest,
					Area, InfectedBy, Recovery);
				break;
			}

			default:
			{
				break;
			}
		}
	}

	else  //Isolated
	{
		GetDlgItemText(txtIsolationAddress, IsolationAddr.street);
		comboIsolationCityController.GetLBText(comboIsolationCityController.GetCurSel(), IsolationAddr.city);
		GetDlgItemText(dtpIsolationEntry, DateBuffer);
		IsolationEntry.day = _ttoi(DateBuffer.Mid(0, 2));
		IsolationEntry.month = _ttoi(DateBuffer.Mid(3, 5));
		IsolationEntry.year = _ttoi(DateBuffer.Mid(6, 10));
		GetDlgItemText(txtExposedID, ExposedTo);
		NewPerson = new Isolated(Gender, ID, Name, Addr, Birthday, IsolationAddr, IsolationEntry, ExposedTo);
	}

	Persons.push_back(NewPerson);
	ClearFieldsOnScreen();
	
	CString temp;
	temp.Format(_T("ID %s has been added"), ID);
	SetDlgItemText(staAddPerson, temp);
	GetDlgItem(staAddPerson)->ShowWindow(SW_SHOW);
}

/*
Function: [Event-Driven] Runs through the persons vector and saves all the data into a personsSave.txt file
*/
void CFinalProjectDlg::OnBnClickedbtnsaveall()
{
	/*
		To add:
			- Needs a proper way to discern if there is a file or not. In case we will need to "Run over" the existing file or not.
			- We need to complete the "User line"
			- Need a way to find a way to pull information of the other types through the Persons. Probably need to add a virtual function for each to see if it can be manipulated that way or not.
	*/
	vector<Person*>::iterator ptr;
	CStdioFile f;
	CString myLine;// , lineBreak, itemBreak;
	CFileException e;
	TCHAR* pszFileName = _T("peopleSave.txt");
	if (!f.Open(pszFileName, CStdioFile::modeCreate | CStdioFile::modeWrite, &e))
	{
		TRACE(_T("File could not be opened %d\n"), e.m_cause);
		return;
	}

	//loading here
	int i = 0;
	ptr = Persons.begin();
	while (ptr != Persons.end())
	{
		//FORMAT: type; id; name; gender; address city; address street; birthday.day; birthday.month; birthday.year;
		myLine.Format(_T("%d; %s; %s; %d; %s; %s; %s; %d; %d; %d; "), Persons[i]->get_itemType(), Persons[i]->get_ID(), Persons[i]->get_Name(), Persons[i]->get_Gender(), Persons[i]->get_Address().city, Persons[i]->get_Address().street, Persons[i]->get_Birthday().day, Persons[i]->get_Birthday().month, Persons[i]->get_Birthday().year);
		f.WriteString(myLine);
		//switch on type
		if (Persons[i]->get_itemType() != 3) {
			//not isolated, dump sick info
			//FORMAT: PositiveTest.day; PositiveTest.month; PositiveTest.year; InfectorID; InfectionArea;
			
			//myLine.Format(_T("%d; %d; %d; %s; %s; "))
			//f.WriteString(myLine);
		}
		switch (Persons[i]->get_itemType())
		{
			case 0://hospitalized
			{
				break;
			}
			case 1://non-hospitalized
			{
				break;
			}
			case 2://recovered
			{
				break;
			}
			case 3://isolated
			{
				break;
			}
			default:
			{
				TRACE(_T("ERROR IN HANDLING DATATYPE INFO DUMP"));
				break;
			}
		}

		i++;
		ptr++;
	}

	f.Close();
	myLine.Format(_T("All %d People have been added"), i+1);
	SetDlgItemText(staAddPerson, myLine);
	GetDlgItem(staAddPerson)->ShowWindow(SW_SHOW);
	/*
	
		list<Person>::iterator ptr;
		ptr = people.begin();
		CStdioFile f;
		CFileException e;
		TCHAR* pszFileName = _T("peopleSave.txt");
		if (!f.Open(pszFileName, CStdioFile::modeCreate | CStdioFile::modeWrite, &e))
		{
			TRACE(_T("File could not be opened %d\n"), e.m_cause);
			return;
		}
		CString myJJ;
		int i = 50;
		while (ptr != people.end())
		{
			myJJ.Format(_T("%d"), i);
			f.WriteString(myJJ);
			f.WriteString(_T("; "));
			myJJ.Format(_T("%s"), ptr._Ptr->_Myval.getName());
			f.WriteString(myJJ);
			f.WriteString(_T("; "));
			myJJ.Format(_T("%d"), ptr._Ptr->_Myval.getInfected());// , ptr._Ptr->_Myval.getName());
			f.WriteString(myJJ);
			f.WriteString(_T(";\n"));
			i++;
			ptr++;
		}

		f.Close();
		SetDlgItemText(IDC_STATIC, pszFileName);
	
	*/
}
