// CGraphDlg.cpp : implementation file
//

//#include "pch.h"
#include "FinalProject.h"
#include "CGraphDlg.h"
#include "afxdialogex.h"


// CGraphDlg dialog

IMPLEMENT_DYNAMIC(CGraphDlg, CDialogEx)

CGraphDlg::CGraphDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRAPH_DIALOG, pParent)
{

}

CGraphDlg::~CGraphDlg()
{
}

void CGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, comboGraphsSelect_GH, comboGraphsSelect_GH_Controller);
}


BEGIN_MESSAGE_MAP(CGraphDlg, CDialogEx)
	ON_BN_CLICKED(btnViewGraph_GH, &CGraphDlg::OnBnClickedViewGraph)
	ON_BN_CLICKED(btnSaveGraphs_GH, &CGraphDlg::OnBnClickedSaveGraphs)
	ON_BN_CLICKED(btnLoadGraphs_GH, &CGraphDlg::OnBnClickedLoadGraphs)
	ON_BN_CLICKED(btnHelpGraph_GH, &CGraphDlg::OnBnClickedHelpGraph)
END_MESSAGE_MAP()

BOOL CGraphDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString te;
	for (int i = 0; i < 5; i++)
	{
		te.Format(_T("Graph Slot %d"), i);
		comboGraphsSelect_GH_Controller.AddString((LPCTSTR)te);
	}
	comboGraphsSelect_GH_Controller.SetCurSel(0);
	return TRUE; // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
// CGraphDlg message handlers


void CGraphDlg::OnBnClickedViewGraph()
{
	//CDialogEx::OnPaint();
	CClientDC pDC(this);
	GraphObject* graph;
	vector <int> info;
	vector <CString> names;
	unsigned int j;
	CString xAxis, yAxis, temp;
	CPoint p;

	j = 0;
	while (j < 10)//fake data for now
	{
		temp.Format(_T("Name_%d"), j);
		info.push_back(j*15 + 25);
		names.push_back(temp);
		j++;
	}
	//to be edited
	xAxis.Format(_T("Insert X Axis %d"), 1);
	yAxis.Format(_T("Insert\nY\nAxis %d"), 1);
	p.x = START_LINE_GRAPH_X;
	p.y = START_LINE_GRAPH_Y;

	graph = new GraphObject(&pDC, p, info, names, xAxis, yAxis); //todo: basically after this, try and make a graphobj vector or something to push the items into
	graph->displayGraph();
	this->zone = graph->unloadGraph();
	graphs.push_back(graph);

	/*
	//What we need here more or less, we need to go to the combo and show that graph
	ClearGraphArea();
	CDialogEx::OnPaint();
	GraphObject* temp;
	CClientDC pDC(this);
	int i = comboGRaphViewController.GetCurSel();

	if (i == -1) {
		MessageBox(L"Select a proper thingy.");
		return;
	}
	temp = dynamic_cast<GraphObject*>(graphs[i]);
	temp->loadExistingGraph(&pDC);
	
	*/
}


void CGraphDlg::OnBnClickedSaveGraphs()
{
	// Choice and open file ostream
	CFileDialog dlg(FALSE, _TEXT("dat"), _TEXT("*.dat"));
	CString fname;
	int res = dlg.DoModal();
	if (res == IDOK)
		fname = dlg.GetPathName();
	graphs_size = graphs.size();
	// write to file
	CFile fOut;
	if (fOut.Open(fname, CFile::modeCreate | CFile::modeWrite))
	{
		CArchive ar(&fOut, CArchive::store);
		ar << graphs_size;
		for (int i = 0; i < graphs_size; i++)
		{
			graphs[i]->Serialize(ar);
		}
		ar.Close();
	}
	fOut.Close();
	Invalidate();
}


void CGraphDlg::OnBnClickedLoadGraphs()
{
	// Choice and open file ostream
	GraphObject* temp;
	CFileDialog dlg(TRUE, _TEXT("dat"), _TEXT("*.dat"));
	CString fname;
	int res = dlg.DoModal();
	if (res == IDOK)
		fname = dlg.GetPathName();

	// load to file
	CFile fOut;
	if (fOut.Open(fname, CFile::modeRead))
	{
		graphs.clear();
		CArchive ar(&fOut, CArchive::load);
		ar >> graphs_size;
		for (int i = 0; i < graphs_size; i++)
		{
			temp = new GraphObject();
			temp->Serialize(ar);
			graphs.push_back(temp);
			DeleteObject(temp);
		}
		ar.Close();
	}
	fOut.Close();
	Invalidate();
}


void CGraphDlg::OnBnClickedHelpGraph()
{
	//MessageBox(L"Currently for clearing the graph.\nTo be changed.");
	ClearGraphArea();
}

void CGraphDlg::ClearGraphArea()
{
	InvalidateRect(zone, true);
}
