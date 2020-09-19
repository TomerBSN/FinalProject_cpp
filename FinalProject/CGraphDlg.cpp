// CGraphDlg.cpp : implementation file
//

#include "pch.h"
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
	DDX_Control(pDX, srGraphScroll_GH, srGraphScroll_Controller);
}


BEGIN_MESSAGE_MAP(CGraphDlg, CDialogEx)
	ON_BN_CLICKED(btnViewGraph_GH, &CGraphDlg::OnBnClickedViewGraph)
	ON_BN_CLICKED(btnSaveGraphs_GH, &CGraphDlg::OnBnClickedSaveGraphs)
	ON_BN_CLICKED(btnLoadGraphs_GH, &CGraphDlg::OnBnClickedLoadGraphs)
	ON_BN_CLICKED(btnHelpGraph_GH, &CGraphDlg::OnBnClickedHelpGraph)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

BOOL CGraphDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	comboGraphsSelect_GH_Controller.SetCurSel(0);
	PredefinedGraphs();
	return TRUE;
}


void CGraphDlg::OnBnClickedViewGraph()
{
	//What we need here more or less, we need to go to the combo and show that graph
	ClearGraphArea();
	CDialogEx::OnPaint();
	GraphObject* temp;
	CClientDC pDC(this);
	int i = comboGraphsSelect_GH_Controller.GetCurSel();

	if (i == -1) {
		MessageBox(L"Select a proper thingy.");
		return;
	}
	if(i > graphs.size()) {
		MessageBox(L"Out of bounds for graphs.");
		return;
	}
	temp = dynamic_cast<GraphObject*>(graphs[i]);
	temp->displayGraph(false, &pDC);
	adjustScrollBar(*temp);
	this->zone = temp->unloadGraph();
}


void CGraphDlg::OnBnClickedSaveGraphs()
{
	// Choice and open file ostream
	CFileDialog dlg(FALSE, _TEXT("dat"), _TEXT("*.dat"));
	CString fname;
	INT_PTR res = dlg.DoModal();
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
	ClearGraphArea();
}


void CGraphDlg::OnBnClickedLoadGraphs()
{
	GraphObject* temp;
	CString fname;
	CFileDialog dlg(TRUE, _TEXT("dat"), _TEXT("*.dat"));
	INT_PTR res = dlg.DoModal(); //ISSUE here for some reason, like it can't bring this modal up and at the end it endlessly loops
	if (res == IDOK)
		fname = dlg.GetPathName();
	CString tp;
	CFile fOut;
	if (fOut.Open(fname, CFile::modeRead))
	{
		graphs.clear();
		CArchive ar(&fOut, CArchive::load);
		
		ar >> graphs_size;
		for (int i = 0; i < graphs_size; i++)
		{
			tp.Format(_T("Loop %d"), i);
			temp = new GraphObject();
			temp->Serialize(ar);
			graphs.push_back(temp);
			DeleteObject(temp);
			
		}

		ar.Close();
	}
	else
	{
		MessageBox(_T("File could not be opened\n"));
		return;
	}
	fOut.Close();
	Invalidate();
	ClearGraphArea();
}


void CGraphDlg::OnBnClickedHelpGraph()
{
	MessageBox(L"Select a graph you wish to see from the delegated section.\nAfter that click on View to see it visually.\n\nIf you intend on viewing these in teh future, please save the graph by clicking on Save.\n\nTo view a old version of a graph click on Load and select the correct file.\nNOTE: Any progress from before will be cleared, best to save beforehand.\n\nEnjoy!");
	ClearGraphArea();
}

void CGraphDlg::ClearGraphArea()
{
	InvalidateRect(zone, true);
}

void CGraphDlg::PredefinedGraphs()
{
	map<CString, int>::iterator itr;
	vector <int> information;
	vector <CString> legendValue;
	CClientDC pDC(this);
	GraphObject* graph;
	CString xAxis, yAxis;
	CPoint p(START_LINE_GRAPH_X, START_LINE_GRAPH_Y);
	yAxis = L"Amount\nof\nSick";

	loadFromMap(CountByHostital, information, legendValue);
	xAxis = L"Hospital Names";
	graph = new GraphObject(&pDC, p, information, legendValue, xAxis, yAxis);
	information.clear(); legendValue.clear();
	graph->displayGraph(true, &pDC);
	graphs.push_back(graph);
	this->zone = graph->unloadGraph();
	ClearGraphArea();

	loadFromMap(CountByArea, information, legendValue);
	xAxis = L"Area Type Names";
	graph = new GraphObject(&pDC, p, information, legendValue, xAxis, yAxis);
	information.clear(); legendValue.clear();
	graph->displayGraph(true, &pDC);
	graphs.push_back(graph);
	this->zone = graph->unloadGraph();
	ClearGraphArea();


	loadFromMap(CountByCity, information, legendValue);
	xAxis = L"City Names";
	graph = new GraphObject(&pDC, p, information, legendValue, xAxis, yAxis);
	information.clear(); legendValue.clear();
	graph->displayGraph(true, &pDC);
	graphs.push_back(graph);
	this->zone = graph->unloadGraph();
	ClearGraphArea();
	
	loadFromMap(CountByLevel, information, legendValue);
	xAxis = L"Sickness Levels";
	graph = new GraphObject(&pDC, p, information, legendValue, xAxis, yAxis);
	information.clear(); legendValue.clear();
	graph->displayGraph(true, &pDC);
	graphs.push_back(graph);
	this->zone = graph->unloadGraph();
	ClearGraphArea();
}

void CGraphDlg::loadFromMap(map<CString, int> &mMap, vector <int> &info, vector <CString> &legendValue)
{
	map<CString, int>::iterator itr;
	for (itr = mMap.begin(); itr != mMap.end(); ++itr)
	{
		legendValue.push_back(itr->first);
		info.push_back(itr->second);
	}

}

void CGraphDlg::adjustScrollBar(GraphObject& grph)
{
	SCROLLINFO ScrollInfo;
	ScrollInfo.cbSize = sizeof(ScrollInfo);     // size of this structure
	ScrollInfo.fMask = SIF_ALL;                 // parameters to set
	ScrollInfo.nMin = 0;                        // minimum scrolling position
	ScrollInfo.nMax = grph.getLength();                      // maximum scrolling position
	ScrollInfo.nPage = 40;                      // the page size of the scroll box
	ScrollInfo.nPos = 50;                       // initial position of the scroll box
	ScrollInfo.nTrackPos = 0;                   // immediate position of a scroll box that the user is dragging
	srGraphScroll_Controller.SetScrollInfo(&ScrollInfo);
}

//void CGraphDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
//{
//	switch (nSBCode)
//	{
//	case SB_BOTTOM:         //Scrolls to the lower right. 
//		break;
//	case SB_ENDSCROLL:      //Ends scroll. 
//		break;
//	case SB_LINEDOWN:       //Scrolls one line down. 
//		srGraphScroll_Controller.SetScrollPos(srGraphScroll_Controller.GetScrollPos() + 1);
//		break;
//	case SB_LINEUP:         //Scrolls one line up. 
//		srGraphScroll_Controller.SetScrollPos(srGraphScroll_Controller.GetScrollPos() - 1);
//		break;
//	case SB_PAGEDOWN:       //Scrolls one page down. 
//		srGraphScroll_Controller.SetScrollPos(srGraphScroll_Controller.GetScrollPos() + srGraphScroll_Controller.GetScrollInfo();
//		break;
//	case SB_PAGEUP:         //Scrolls one page up. 
//		SetScrollPos(GetScrollPos() - ScrollInfo.nPage);
//		break;
//	case SB_THUMBPOSITION:  //The user has dragged the scroll box (thumb) and released the mouse button. The nPos parameter indicates the position of the scroll box at the end of the drag operation. 
//		break;
//	case SB_THUMBTRACK:     //The user is dragging the scroll box. This message is sent repeatedly until the user releases the mouse button. The nPos parameter indicates the position that the scroll box has been dragged to. 
//		srGraphScroll_Controller.SetScrollPos(nPos);
//		break;
//	case SB_TOP:            //Scrolls to the upper left. 
//		break;
//		CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
//}
