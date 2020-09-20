#define _CRT_SECURE_NO_WARNINGS
// FinalProjectDlg.cpp : implementation file

#include "stdafx.h"
#include "FinalProject.h"
#include "FinalProjectDlg.h"
#include "afxdialogex.h"
#include "CGraphDlg.h"
#include "CSearchDlg.h"
#include "Hospitalized.h"
#include "NonHospitalized.h"
#include "Recovered.h"
#include "Isolated.h"
#include "Global.h"

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
	DDX_Control(pDX, comboInfectionAreaType, comboInfectionAreaTypeController);
	DDX_Control(pDX, comboIsolationCity, comboIsolationCityController);
	DDX_Control(pDX, comboHospital, comboHospitalController);
	DDX_Control(pDX, comboSicknessLevel, comboSicknessLevelController);
	DDX_Control(pDX, comboVentilated, comboVentilatedController);
	DDX_Control(pDX, comboCity, comboCityController);
	DDX_Control(pDX, dtpBirthDate, dtpBirthDateController);
	DDX_Control(pDX, dtpPositiveTest, dtpPositiveTestController);
	DDX_Control(pDX, dtpHospitalEntry, dtpHospitalEntryController);
	DDX_Control(pDX, dtpIsolationEntry, dtpIsolationEntryController);
	DDX_Control(pDX, dtpRecoveryDate, dtpRecoveryDateController);
	DDX_Control(pDX, btnSearch, comboSearchController);
	DDX_Control(pDX, txtID, txtIDController);
	DDX_Control(pDX, txtFullName, txtFullNameController);
	DDX_Control(pDX, txtAddress, txtAddressController);
	DDX_Control(pDX, txtIsolationAddress, txtIsolationAddressController);
	DDX_Control(pDX, txtExposedID, txtExposedIDController);
	DDX_Control(pDX, txtInfectorID, txtInfectorIDController);
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
	ON_BN_CLICKED(btnSaveDetails, &CFinalProjectDlg::OnBnClickedbtnsavedetails)
	ON_WM_DESTROY()
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
	
	// Comboboxes + counters initialization
	for (int i = 0; i < NUM_OF_CITYS; i++) {
		comboCityController.InsertString(i, Citys[i]);
		comboIsolationCityController.InsertString(i, Citys[i]);
		Counters.CountByCity[Citys[i]] = 0;
	}
	for (int i = 0; i < NUM_OF_HOSPITALS; i++) {
		comboHospitalController.InsertString(i, Hospitals[i]);
		Counters.CountByHostital[Hospitals[i]] = 0;
	}
	for (int i = 0; i < NUM_OF_INFECTIONAREAS; i++) {
		comboInfectionAreaTypeController.InsertString(i, InfectionAreas[i]);
		Counters.CountByArea[InfectionAreas[i]] = 0;
	}
	for (int i = 0; i < NUM_OF_LEVELS; i++) {
		Counters.CountByLevel[SicknessLVL[i]] = 0;
	}

	Counters.TotalHospitalized = 0;
	Counters.TotalNonHospitalized = 0;
	Counters.TotalSicks = 0;
	Counters.TotalRecovered = 0;
	Counters.TotalIsolated = 0;
	Counters.TotalVentilated = 0;
	
	comboDataTypeController.SetCurSel(0); // percaution so the user does not create a incorrect type of person into this field.

	// Loads the persons vector from the personsSave.txt file properly.
	
		TCHAR* fname = _T("peopleSave.txt");
		CString wholeStr = loadFile(fname);
		if(!(wholeStr.IsEmpty()))
			fillCstringList(wholeStr);

	Clear_InvalidIsolated();         // clean all isolated persons whose their isolation period has finished

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
	
	switch (comboDataTypeController.GetCurSel())	//	Hospitalized; Not Hospitalized; Recovered; Self Isolation;
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
			break;
	}
	GetDlgItem(btnCreate)->EnableWindow(false);
	comboDataTypeController.EnableWindow(false);
	GetDlgItem(btnAddPerson)->EnableWindow(true);
	comboSearchController.EnableWindow(false);
}

/*
Function: [Event-Driven] When clicking the button it will reset the window to its clear position without any oddities.
*/
void CFinalProjectDlg::OnBnClickedbtnclearall()
{
	ClearFieldsOnScreen();
	GetDlgItem(staAddPerson)->ShowWindow(SW_HIDE);
}

/*
Function: [Event-Driven] Will reset all the corresponding fields within the main Dialog Window.
*/
void CFinalProjectDlg::ClearFieldsOnScreen()
{
	CString cs;
	cs.Format(_T(""));
	SetDlgItemText(txtID, cs);
	SetDlgItemText(txtAddress, cs);
	SetDlgItemText(txtFullName, cs);
	SetDlgItemText(txtInfectorID, cs);
	SetDlgItemText(txtIsolationAddress, cs);
	comboDataTypeController.SetCurSel(0);		// always put it as 0, -1 can cause user generated issues.
	comboGenderController.SetCurSel(-1);
	comboHospitalController.SetCurSel(-1);
	comboInfectionAreaTypeController.SetCurSel(-1);
	comboIsolationCityController.SetCurSel(-1);
	comboSicknessLevelController.SetCurSel(-1);
	comboVentilatedController.SetCurSel(-1);
	comboCityController.SetCurSel(-1);

	for (int i = 1; i <= 5; i++) ToggleVisibilty(false, i);
	GetDlgItem(btnCreate)->EnableWindow(true);
	comboSearchController.EnableWindow(true);
	comboDataTypeController.EnableWindow(true);
	GetDlgItem(btnAddPerson)->EnableWindow(false);
	GetDlgItem(btnSaveDetails)->ShowWindow(SW_HIDE);
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
		case 1:		// chunk 1 - top rank
		{
			GetDlgItem(staHeader1)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
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
			break;
		}
		case 2:		// chunk 2 - all* second tier
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
		case 3:		// chunk 3 - isolated
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
		case 4:		// chunk 4 - hospital
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
		case 5:		// chunk 5 - recovered
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
	CDC* dc = comboGenderController.GetDC();
	dc->SetBkColor(COLORREF(RGB(255, 0, 0)));
	int selectedForm = comboDataTypeController.GetCurSel();
	if (!checkUserInputData(selectedForm))	// Implements a function that validate data of all inputs
		return;

	Person* NewPerson = NULL;
	bool Gender, IsVentilated;
	Address Addr, IsolationAddr;
	Date Birthday, PositiveTest, HospitalEntry, Recovery, IsolationEntry;
	CString ID, Name, DateBuffer, InfectedBy, ExposedTo, Hospital, Level, Area, temp = _T("");
	
	Gender = comboGenderController.GetCurSel();
	GetDlgItemText(txtID, ID);
	GetDlgItemText(txtFullName, Name);
	GetDlgItemText(txtAddress, Addr.street);
	comboCityController.GetLBText(comboCityController.GetCurSel(), Addr.city);
	GetDlgItemText(dtpBirthDate, DateBuffer);
	Birthday.day = _ttoi(DateBuffer.Mid(0, 2));
	Birthday.month = _ttoi(DateBuffer.Mid(3, 5));
	Birthday.year = _ttoi(DateBuffer.Mid(6, 10));

	if (selectedForm != 3)		// Sick objects
	{
		GetDlgItemText(dtpPositiveTest, DateBuffer);
		PositiveTest.day = _ttoi(DateBuffer.Mid(0, 2));
		PositiveTest.month = _ttoi(DateBuffer.Mid(3, 5));
		PositiveTest.year = _ttoi(DateBuffer.Mid(6, 10));
		GetDlgItemText(txtInfectorID, InfectedBy);
		comboInfectionAreaTypeController.GetLBText(comboInfectionAreaTypeController.GetCurSel(), Area);
	}

	switch (selectedForm)	// Hospitalized; Not Hospitalized; Recovered; Self Isolation;
	{
		case 0:		// Hospitalized
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

		case 1:		// Not Hospitalized
		{
			GetDlgItemText(txtIsolationAddress, IsolationAddr.street);
			comboIsolationCityController.GetLBText(comboIsolationCityController.GetCurSel(), IsolationAddr.city);
			NewPerson = new NonHospitalized(Gender, ID, Name, Addr, Birthday,
				PositiveTest, Area, InfectedBy, IsolationAddr);
			break;
		}

		case 2:	   // Recovered
		{
			GetDlgItemText(dtpRecoveryDate, DateBuffer);
			Recovery.day = _ttoi(DateBuffer.Mid(0, 2));
			Recovery.month = _ttoi(DateBuffer.Mid(3, 5));
			Recovery.year = _ttoi(DateBuffer.Mid(6, 10));
			NewPerson = new Recovered(Gender, ID, Name, Addr, Birthday, PositiveTest,
				Area, InfectedBy, Recovery);
			break;
		}

		case 3:		// Isolated
		{
			GetDlgItemText(txtIsolationAddress, IsolationAddr.street);
			comboIsolationCityController.GetLBText(comboIsolationCityController.GetCurSel(), IsolationAddr.city);
			GetDlgItemText(dtpIsolationEntry, DateBuffer);
			IsolationEntry.day = _ttoi(DateBuffer.Mid(0, 2));
			IsolationEntry.month = _ttoi(DateBuffer.Mid(3, 5));
			IsolationEntry.year = _ttoi(DateBuffer.Mid(6, 10));
			GetDlgItemText(txtExposedID, ExposedTo);
			NewPerson = new Isolated(Gender, ID, Name, Addr, Birthday, IsolationAddr, IsolationEntry, ExposedTo);
			break;
		}

		default:
			break;
	}
	
	if (callfromSearch)     // handle case that this function called by edit/update option
	{
		Persons[searchPersonID] = NewPerson;
		temp.Format(_T("ID %s has been edited"), (LPCTSTR)ID);
	}

	else
	{
		Persons.push_back(NewPerson);
		temp.Format(_T("ID %s has been added"), (LPCTSTR)ID);
	}

	updateCounters(NewPerson, true);
	ClearFieldsOnScreen();
	SetDlgItemText(staAddPerson, temp);
	GetDlgItem(staAddPerson)->ShowWindow(SW_SHOW);
}

/*
Function: [void] Goes through the whole dialog inputs and checks to see if all the data is accurately inputed.
	- ID must be a number at a length of up to 9 digits.
	- Dates must not conflict
	- Checks the allocation of the strings.

	If the input is incorrect it will pop a message box and return false.
*/
bool CFinalProjectDlg::checkUserInputData(int selectedForm)
{
	bool isCorrect = true;
	CString fullMsg, temp, BirthdayBuffer, PositiveTestBuffer, HospitalEntryBuffer, RecoveryBuffer, IsolationEntryBuffer;
	GetDlgItemText(dtpBirthDate, BirthdayBuffer);
	fullMsg.Format(_T("You have one of the following problems:\n 1. ID is not 9 digits long or is already exists in system\n 2. Empty necessary details\n 3. Dates are not make sene"));

	GetDlgItemText(txtFullName, temp);
	ValidateUserInput(txtFullNameController, isCorrect, temp);

	ValidateUserInput(comboGenderController, isCorrect);
	ValidateUserInput(comboCityController, isCorrect);

	GetDlgItemText(txtAddress, temp);
	ValidateUserInput(txtAddressController, isCorrect, temp);

	//check the ID here
	GetDlgItemText(txtID, temp);
	if (temp.GetLength() != 9) {
		SetBorderColor(txtIDController, 255, 0, 0);
		isCorrect = false;
	}

	else if (searchPersonByID(temp) && !callfromSearch)
	{
		SetBorderColor(txtIDController, 255, 0, 0);
		isCorrect = false;
	}

	else
		SetBorderColor(txtIDController, 0, 255, 0);

	if (selectedForm != 3)	// if it has Sick.h properties
	{
		GetDlgItemText(txtInfectorID, temp);
		if (temp.GetLength())
		{
			if (temp.GetLength() != 9)
			{
				SetBorderColor(txtInfectorIDController, 255, 0, 0);
				isCorrect = false;
			}
			else
				SetBorderColor(txtInfectorIDController, 0, 255, 0);
		}

		ValidateUserInput(comboInfectionAreaTypeController, isCorrect);

		GetDlgItemText(dtpPositiveTest, PositiveTestBuffer);
		ValidateUserInput(dtpPositiveTestController, isCorrect, PositiveTestBuffer, BirthdayBuffer);
	}
	//switch between the type of the person data then check as per that
	switch (selectedForm)
	{
		case 0:		// Hospitalized
		{
			GetDlgItemText(dtpHospitalEntry, HospitalEntryBuffer);

			ValidateUserInput(dtpHospitalEntryController, isCorrect, HospitalEntryBuffer, BirthdayBuffer);
			ValidateUserInput(dtpHospitalEntryController, isCorrect, HospitalEntryBuffer, PositiveTestBuffer);
			ValidateUserInput(comboHospitalController, isCorrect);
			ValidateUserInput(comboSicknessLevelController, isCorrect);
			ValidateUserInput(comboVentilatedController, isCorrect);
			break;
		}

		case 1:		// Non-Hospitalized
		{
			GetDlgItemText(txtIsolationAddress, temp);
			ValidateUserInput(txtIsolationAddressController, isCorrect, temp);
			ValidateUserInput(comboIsolationCityController, isCorrect);
			break;
		}
		case 2:		// Recovered
		{
			GetDlgItemText(dtpRecoveryDate, RecoveryBuffer);
			ValidateUserInput(dtpRecoveryDateController, isCorrect, RecoveryBuffer, BirthdayBuffer);
			ValidateUserInput(dtpRecoveryDateController, isCorrect, RecoveryBuffer, PositiveTestBuffer);
			break;
		}
		case 3:		// Isolated
		{
			GetDlgItemText(dtpIsolationEntry, IsolationEntryBuffer);
			ValidateUserInput(dtpIsolationEntryController, isCorrect, IsolationEntryBuffer, BirthdayBuffer);

			GetDlgItemText(txtIsolationAddress, temp);
			ValidateUserInput(txtIsolationAddressController, isCorrect, temp);

			GetDlgItemText(txtExposedID, temp);
			if (temp.GetLength())
			{
				if (temp.GetLength() != 9)
				{
					SetBorderColor(txtExposedIDController, 255, 0, 0);
					isCorrect = false;
				}
				else
					SetBorderColor(txtExposedIDController, 0, 255, 0);
			}

			ValidateUserInput(comboIsolationCityController, isCorrect);
			break;
		}
		default:
			break;
	}

	//pops message box if needed
	if (!isCorrect) MessageBox((LPCTSTR)fullMsg);
	return isCorrect;
}

/*
Function: [Event-Driven] Save all persons to file
*/
void CFinalProjectDlg::OnBnClickedbtnsaveall()
{
	savePersonsToFile();
}

/*
Function: [Event-Driven] Runs through the persons vector and saves all the data into a personsSave.txt file
*/
void CFinalProjectDlg::savePersonsToFile()
{
	/*
		Formatting rules:
			- Dates: Day -> Month -> Year
			- Address: City -> Street
			- Do it by the way the class members appear in each class.
	*/

	vector<Person*>::iterator ptr;
	CStdioFile f;
	CString myLine;
	CFileException e;
	TCHAR* pszFileName = _T("peopleSave.txt");
	if (!f.Open(pszFileName, CStdioFile::modeCreate | CStdioFile::modeWrite, &e))
	{
		myLine.Format(_T("Error in opening pszFileName/Path at:\n%s\nFile could not be opened %d"), (LPCTSTR)pszFileName, e.m_cause);
		MessageBox((LPCTSTR)myLine);
		TRACE(_T("File could not be opened %d\n"), e.m_cause);
		return;
	}

	// loading here
	int i = 0;
	ptr = Persons.begin();
	while (ptr != Persons.end())
	{
		// Base FORMAT: type; id; name; gender; address city; address street; birthday.day; birthday.month; birthday.year;
		
		myLine.Format(_T("%d;%s;%s;%d;%s;%s;%d;%d;%d;"), Persons[i]->get_itemType(), (LPCTSTR)Persons[i]->get_ID(), (LPCTSTR)Persons[i]->get_Name(), Persons[i]->get_Gender(), (LPCTSTR)Persons[i]->get_Address().city, (LPCTSTR)Persons[i]->get_Address().street, Persons[i]->get_Birthday().day, Persons[i]->get_Birthday().month, Persons[i]->get_Birthday().year);//No need for dynamic cast since i can reach these class members.
		f.WriteString((LPCTSTR)myLine);

		switch (Persons[i]->get_itemType())
		{
			case 0:		// Hospitalized
			{
				// format: Level; isVentilatyed; Hospital; HospitalizationDate.day; HD.month; HD.year;
				Hospitalized *hos = (Hospitalized*)(Persons[i]);
				myLine.Format(_T("%d;%d;%d;%s;%s;%d;%s;%d;%d;%d;%s#"), hos->get_PositiveTest_date().day, hos->get_PositiveTest_date().month, hos->get_PositiveTest_date().year, (LPCTSTR)hos->get_InfectionArea(), (LPCTSTR)hos->get_Level(), hos->get_IsVentilated(), (LPCTSTR)hos->get_Hospital(), hos->get_HospitalizationDate().day, hos->get_HospitalizationDate().month, hos->get_HospitalizationDate().year, (LPCTSTR)hos->get_InfectedBy());
				f.WriteString((LPCTSTR)myLine);
				break;
			}
			case 1:		// Non-Hospitalized
			{
				//format: whereIsolated city; whereIsolated street;
				NonHospitalized* nonhos = (NonHospitalized*)(Persons[i]);
				myLine.Format(_T("%d;%d;%d;%s;%s;%s;%s;#"), nonhos->get_PositiveTest_date().day, nonhos->get_PositiveTest_date().month, nonhos->get_PositiveTest_date().year, (LPCTSTR)nonhos->get_InfectionArea(), (LPCTSTR)nonhos->get_WhereIsolated().city, (LPCTSTR)nonhos->get_WhereIsolated().street, (LPCTSTR)nonhos->get_InfectedBy());
				f.WriteString((LPCTSTR)myLine);
				break;
			}
			case 2:		//Recovered
			{
				// format: recovery,day; recovery.month; recovery.year;
				Recovered* rec = (Recovered*)(Persons[i]);
				myLine.Format(_T("%d;%d;%d;%s;%d;%d;%d;%s#"), rec->get_PositiveTest_date().day, rec->get_PositiveTest_date().month, rec->get_PositiveTest_date().year, (LPCTSTR)rec->get_InfectionArea(), rec->get_RecoveryDate().day, rec->get_RecoveryDate().month, rec->get_RecoveryDate().year, (LPCTSTR)rec->get_InfectedBy());
				f.WriteString((LPCTSTR)myLine);
				break;
			}
			case 3:		// Isolated
			{
				// format: whereIsolated.city; whereisolated.street; isolateddate.day; isolation.month; isolation.year; ExpostedTo;
				Isolated* iso = (Isolated*)(Persons[i]);
				myLine.Format(_T("%s;%s;%d;%d;%d;%s;#"), (LPCTSTR)iso->get_WhereIsolated().city, (LPCTSTR)iso->get_WhereIsolated().street, iso->get_Isolation_date().day, iso->get_Isolation_date().month, iso->get_Isolation_date().year, (LPCTSTR)iso->get_ExposedTo());
				f.WriteString((LPCTSTR)myLine);
				break;
			}
			default:
			{
				myLine.Format(_T("Error in handling get_itemType()\nPerson ID: %s; Type: %d;"), (LPCTSTR)Persons[i]->get_ID(), Persons[i]->get_itemType());
				MessageBox((LPCTSTR)myLine);
				TRACE(_T("ERROR IN HANDLING DATATYPE INFO DUMP"));
				break;
			}
		}
		myLine.Format(_T("\n"));
		f.WriteString(myLine);
		i++;
		ptr++;
	}

	f.Close();
	myLine.Format(_T("All %d People have been saved"), i);
	SetDlgItemText(staAddPerson, myLine);
	GetDlgItem(staAddPerson)->ShowWindow(SW_SHOW);
}

/*
Function: [void] Gets a CString that has all the user inputed info from a previous run, and "chops" the data into proper formatting, adding each line of data as a new person within the persons vector
*/
void CFinalProjectDlg::fillCstringList(CString wholeFile)
{
	vector <CString> wholePersonItemList = seperateLine(wholeFile, (LPCTSTR)_T("#"));
	vector <CString> singlePersonItemList;
	Person* per;
	int itemType, whole = 0, single;
	bool Gender, IsVentilated;
	Address Addr, IsolationAddr;
	Date Birthday, PositiveTest, HospitalEntry, Recovery, IsolationEntry;
	CString ID, Name, DateBuffer, InfectedBy, ExposedTo, Hospital, Level, Area, line;
	while (!wholePersonItemList[whole].IsEmpty())
	{
		line = wholePersonItemList[whole];
		singlePersonItemList = seperateLine(line, (LPCTSTR)_T(";"));	// split new line
		single = 0;

		// Base FORMAT: type; id; name; gender; address city; address street; birthday.day; birthday.month; birthday.year;

		itemType = _ttoi(singlePersonItemList[single++]);
		ID = singlePersonItemList[single++];
		Name = singlePersonItemList[single++];
		Gender = _ttoi(singlePersonItemList[single++]);
		Addr.city = singlePersonItemList[single++];
		Addr.street = singlePersonItemList[single++];
		Birthday.day = _ttoi(singlePersonItemList[single++]);
		Birthday.month = _ttoi(singlePersonItemList[single++]);
		Birthday.year = _ttoi(singlePersonItemList[single++]);

		if (itemType != 3)	// Not Isolated, so it needs Sick class members
		{
			// Sick FORMAT: PositiveTest.day; PositiveTest.month; PositiveTest.year; InfectorID; InfectionArea;
			PositiveTest.day = _ttoi(singlePersonItemList[single++]);
			PositiveTest.month = _ttoi(singlePersonItemList[single++]);
			PositiveTest.year = _ttoi(singlePersonItemList[single++]);
			Area = singlePersonItemList[single++];
		}
		switch (itemType)
		{
			case 0:		// Hospitalized format: Level; isVentilatyed; Hospital; HospitalizationDate.day; HD.month; HD.year;
			{
				Level = singlePersonItemList[single++];
				IsVentilated = _ttoi(singlePersonItemList[single++]);
				Hospital = singlePersonItemList[single++];
				HospitalEntry.day = _ttoi(singlePersonItemList[single++]);
				HospitalEntry.month = _ttoi(singlePersonItemList[single++]);
				HospitalEntry.year = _ttoi(singlePersonItemList[single++]);
				InfectedBy = singlePersonItemList[single++];
				per = new Hospitalized(Gender, ID, Name, Addr, Birthday, PositiveTest, Area, InfectedBy, Level, IsVentilated, Hospital, HospitalEntry);
				break;
			}
			case 1:		// Non-Hospitalized: whereIsolated city; whereIsolated street;
			{
				IsolationAddr.city = singlePersonItemList[single++];
				IsolationAddr.street = singlePersonItemList[single++];
				InfectedBy = singlePersonItemList[single++];
				per = new NonHospitalized(Gender, ID, Name, Addr, Birthday, PositiveTest, Area, InfectedBy, IsolationAddr);
				break;
			}
			case 2:		// Recovered format: recovery,day; recovery.month; recovery.year;
			{
				Recovery.day = _ttoi(singlePersonItemList[single++]);
				Recovery.month = _ttoi(singlePersonItemList[single++]);
				Recovery.year = _ttoi(singlePersonItemList[single++]);
				InfectedBy = singlePersonItemList[single++];
				per = new Recovered(Gender, ID, Name, Addr, Birthday, PositiveTest, Area, InfectedBy, Recovery);
				break;
			}
			case 3:		//Isolated format: whereIsolated.city; whereisolated.street; isolateddate.day; isolation.month; isolation.year; ExpostedTo;
			{
				IsolationAddr.city = singlePersonItemList[single++];
				IsolationAddr.street = singlePersonItemList[single++];
				IsolationEntry.day = _ttoi(singlePersonItemList[single++]);
				IsolationEntry.month = _ttoi(singlePersonItemList[single++]);
				IsolationEntry.year = _ttoi(singlePersonItemList[single++]);
				ExposedTo = singlePersonItemList[single++];
				per = new Isolated(Gender, ID, Name, Addr, Birthday, IsolationAddr, IsolationEntry, ExposedTo);
				break;
			}
			default:
			{
				MessageBox(_T("Error at fillCstringList"));
				break;
			}
		}
		Persons.push_back(per);
		updateCounters(per, true);
		whole++;
	}
}

/*
Function: [vector] Gets a line and seperator that will tokenize the line, returning a list of the untokenized CString that we got.
*/
vector <CString> CFinalProjectDlg::seperateLine(CString theLine, CString seperator)
{
	vector <CString> myList;
	int pos = 0;
	CString tokenLine = theLine.Tokenize(seperator, pos);
	myList.push_back(tokenLine);
	while (!tokenLine.IsEmpty())
	{
		tokenLine = theLine.Tokenize(seperator, pos);
		myList.push_back(tokenLine);
	}
	return myList;
}

/*
Function: [CString] Gets a TCHAR* which is the filename, and if accessable, it will place all the data from
that file into a CString, returning it.
*/
CString CFinalProjectDlg::loadFile(TCHAR* FileName)
{
	CStdioFile f;
	CString line = _T(""), error, wholeStr = _T("");
	CFileException e;
	TCHAR* pszFileName = _T("peopleSave.txt");
	if (!f.Open(pszFileName, CStdioFile::modeRead, &e))
	{
		TRACE(_T("File could not be opened %d\n"), e.m_cause);
		return NULL;
	}

	f.SeekToBegin();
	while (f.ReadString(line))
	{
		if (!line.IsEmpty())
		{
			wholeStr += line;
		}
	}
	f.Close();
	return wholeStr;
}

/*
Function: [void] Remove all isolated person whose their isolation period has finished
*/
void CFinalProjectDlg::Clear_InvalidIsolated()
{
	Date current;
	int i, toDel;
	vector<Person*>::iterator ptr;
	vector<int> toDel_inds;

	// find all indexes that need to be deleted.
	ptr = Persons.begin();
	for (i = 0, ptr = Persons.begin(); ptr != Persons.end(); i++, ptr++)
	{
		if ((*ptr)->get_itemType() == 3)
		{
			time_t curr_time = time(0);	     // get current time
			tm* now = localtime(&curr_time);
			current.year = now->tm_year + 1900;
			current.month = now->tm_mon + 1;
			current.day = now->tm_mday;
			int diff = getDatesDiff(((Isolated*)(*ptr))->get_Isolation_date(), current);
			if (diff >= 14)					// two weeks left from isolation entry date
				toDel_inds.push_back(i);
		}
	}

	// remove all relevant isolated persons by their index
	for (i = 0; i < toDel_inds.size(); i++)
	{
		toDel = toDel_inds[i] - i;
		updateCounters(Persons[toDel], false);
		Persons.erase(Persons.begin() + (toDel));	// if person was deleted, number of items decreased in 1
	}
}

/*
Function: [Event-Driven] Will bring up the IDD_SEARCH_DIALOG.
*/
void CFinalProjectDlg::OnBnClickedbtnsearch()
{
	CSearchDlg search;
	int status = search.DoModal();

	if (status >= 5)		// if user choose update status or edit current details
	{
		status -= 5;        // decrease in 5 to get the object itemType that the user want to change to
		int itemType = Persons[searchPersonID]->get_itemType();
		comboDataTypeController.SetCurSel(status);
		GetDlgItem(btnSaveDetails)->ShowWindow(SW_SHOW);
		this->OnBnClickedbtncreate();
		GetDlgItem(btnAddPerson)->EnableWindow(false);
		comboSearchController.EnableWindow(false);
		SetDlgItemText(txtID, Persons[searchPersonID]->get_ID());
		SetDlgItemText(txtFullName, Persons[searchPersonID]->get_Name());
		Date birthday = Persons[searchPersonID]->get_Birthday();
		CTime birthdayTime(birthday.year, birthday.month, birthday.day, 0, 0, 0);
		dtpBirthDateController.SetTime(&birthdayTime);
		comboGenderController.SetCurSel(Persons[searchPersonID]->get_Gender());
		int city = distance(Citys, find(Citys, Citys + NUM_OF_CITYS, Persons[searchPersonID]->get_Address().city));
		comboCityController.SetCurSel(city);
		SetDlgItemText(txtAddress, Persons[searchPersonID]->get_Address().street);

		if (status != 3 && itemType != 3)		// Show Sick objects props
		{
			Sick *tempSick = (Sick*)(Persons[searchPersonID]);

			Date positivetest = tempSick->get_PositiveTest_date();
			CTime positivetestTime(positivetest.year, positivetest.month, positivetest.day, 0, 0, 0);
			dtpPositiveTestController.SetTime(&positivetestTime);
			SetDlgItemText(txtInfectorID, tempSick->get_InfectedBy());
			int area = distance(InfectionAreas, find(InfectionAreas, InfectionAreas + NUM_OF_INFECTIONAREAS,
				tempSick->get_InfectionArea()));
			comboInfectionAreaTypeController.SetCurSel(area);
		}

		if (status == itemType)				   // edit current details without changing type
		{ 
			switch (status)
			{
				case 0:		// Hospitalized
				{
					Hospitalized* tempHospitalized = (Hospitalized*)(Persons[searchPersonID]);

					Date hospitalentry = tempHospitalized->get_HospitalizationDate();
					CTime hospitalentrytTime(hospitalentry.year, hospitalentry.month, hospitalentry.day, 0, 0, 0);
					dtpHospitalEntryController.SetTime(&hospitalentrytTime);
					int hospital = distance(Hospitals, find(Hospitals, Hospitals + NUM_OF_HOSPITALS,
						tempHospitalized->get_Hospital()));
					comboHospitalController.SetCurSel(hospital);
					int level = distance(SicknessLVL, find(SicknessLVL, SicknessLVL + NUM_OF_LEVELS,
						tempHospitalized->get_Level()));
					comboSicknessLevelController.SetCurSel(level);
					comboVentilatedController.SetCurSel(tempHospitalized->get_IsVentilated());
					break;
				}

				case 1:		// NonHospitalized
				{
					NonHospitalized* tempNonHospitalized = (NonHospitalized*)(Persons[searchPersonID]);

					SetDlgItemText(txtIsolationAddress, tempNonHospitalized->get_WhereIsolated().street);
					int isolationcity_h = distance(Citys, find(Citys, Citys + NUM_OF_CITYS,
						tempNonHospitalized->get_WhereIsolated().city));
					comboIsolationCityController.SetCurSel(isolationcity_h);
					break;
				}
				case 2:		// Recovered
				{
					Recovered* tempRecovered = (Recovered*)(Persons[searchPersonID]);

					Date recovery = tempRecovered->get_RecoveryDate();
					CTime recoveryTime(recovery.year, recovery.month, recovery.day, 0, 0, 0);
					dtpRecoveryDateController.SetTime(&recoveryTime);
					break;
				}
				case 3:		// Isolated
				{
					Isolated* tempIsolated = (Isolated*)(Persons[searchPersonID]);

					Date isolationentry = tempIsolated->get_Isolation_date();
					CTime isolationentryTime(isolationentry.year, isolationentry.month, isolationentry.day, 0, 0, 0);
					dtpIsolationEntryController.SetTime(&isolationentryTime);
					SetDlgItemText(txtIsolationAddress, tempIsolated->get_WhereIsolated().street);
					int isolationcity_i = distance(Citys, find(Citys, Citys + NUM_OF_CITYS,
						tempIsolated->get_WhereIsolated().city));
					comboIsolationCityController.SetCurSel(isolationcity_i);
					SetDlgItemText(txtExposedID, tempIsolated->get_ExposedTo());
					break;
				}

				default:
					break;
			}
		}
	}
}

/*
Function: [Event-Driven] User finished to edit / update person, and clicked save details
*/
void CFinalProjectDlg::OnBnClickedbtnsavedetails()
{
	updateCounters(Persons[searchPersonID], false);  // decrease counters in 1
	callfromSearch = 1;
	OnBnClickedbtnaddperson();
	callfromSearch = 0;
	GetDlgItem(btnSaveDetails)->ShowWindow(SW_HIDE);
}

/*
Function: [void] validate user input of cEdit or CDateTimeCtrl
*/
template <class T>
void CFinalProjectDlg::ValidateUserInput(T& Controller, bool& isCorrect, CString Item1, CString Item2)
{
	bool temp_isCorrect = true;
	if (is_same<T, CEdit>::value)
	{
		if (Item1.IsEmpty())
			temp_isCorrect = false;
	}

	else if (is_same<T, CDateTimeCtrl>::value)
	{
		Date a, b;
		a.day = _ttoi(Item1.Mid(0, 2));
		a.month = _ttoi(Item1.Mid(3, 5));
		a.year = _ttoi(Item1.Mid(6, 10));
		b.day = _ttoi(Item2.Mid(0, 2));
		b.month = _ttoi(Item2.Mid(3, 5));
		b.year = _ttoi(Item2.Mid(6, 10));
		if (getDatesDiff(b, a) < 0)
			temp_isCorrect = false;
	}

	if (temp_isCorrect)
		SetBorderColor(Controller, 0, 255, 0);       // Green
	else
	{
		SetBorderColor(Controller, 255, 0, 0);       // Red
		isCorrect = false;
	}
}

/*
Function: [void] validate user input of CComboBox
*/
void CFinalProjectDlg::ValidateUserInput(CComboBox& Controller, bool& isCorrect)
{
	if (Controller.GetCurSel() == -1)
	{
		SetBorderColor(Controller, 255, 0, 0);
		isCorrect = false;
	}
	else
		SetBorderColor(Controller, 0, 255, 0);

}

/*
Function: [void] Set border color of CWnd objects
*/
template <class T>
void CFinalProjectDlg::SetBorderColor(T& Controller, int R, int G, int B)
{
	CDC* dc = Controller.GetDC();
	dc->SetBkColor(RGB(0, 0, 0));
	CRect rc;
	Controller.GetClientRect(rc);
	dc->SetTextColor(COLORREF(RGB(255, 0, 0)));
	HBRUSH hBrush = CreateSolidBrush(COLORREF(RGB(R, G, B)));
	FrameRect(dc->m_hDC, rc, hBrush);
	DeleteObject(hBrush);
	ReleaseDC(dc);
}

/*
Function: [Event-Driven] User has closed the application window
*/
void CFinalProjectDlg::OnDestroy()
{
	savePersonsToFile();
	CDialogEx::OnDestroy();
}
