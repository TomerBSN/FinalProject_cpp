#define _CRT_SECURE_NO_WARNINGS
// FinalProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FinalProject.h"
#include "FinalProjectDlg.h"
#include "afxdialogex.h"
#include "CGraphDlg.h"
#include "CSearchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	DDX_Control(pDX, comboDataType, comboDataTypeController);
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

	// TODO: Add extra initialization here

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
	ToggleVisibilty(true, 1);
	
	switch (comboDataTypeController.GetCurSel())//Hospitalized;Not Hospitalized;Recovered;Self Isolation;
	{
		case 0://Hospitalized
		{
			ToggleVisibilty(true, 2);
			ToggleVisibilty(true, 4);
			//Add a Hospitalized Object here, then refer to load info function
			break;
		}
		case 1://Not Hospitalized
		{
			ToggleVisibilty(true, 2);
			ToggleVisibilty(true, 3);
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
			ToggleVisibilty(true, 2);
			ToggleVisibilty(true, 3);
			break;
		}
		default:
		{
			//Normally will go to Recovered one, or Self Isolation

			break;
		}
	}


	//optional: lock the create button until add_person is clicked or if clear all is clicked?
}

void CFinalProjectDlg::OnBnClickedbtnclearall()
{
	// TODO: clear the text and all that shit.

	for (int i = 1; i <= 5; i++) ToggleVisibilty(false, i);
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
			break;
		}
		case 3://chunk 3 - isolated
		{
			GetDlgItem(staHeader2)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staIsolatedCity)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(comboIsolationCity)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);
			GetDlgItem(staIsolatedAddress)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);//
			GetDlgItem(txtIsolationAddress)->ShowWindow(visiblity ? SW_SHOW : SW_HIDE);//
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