#include "pch.h"
#include "FinalProject.h"
#include "CGraphDlg.h"
#include "afxdialogex.h"
#include <algorithm>


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
	comboGraphsSelect_GH_Controller.SetCurSel(0);//Forcing the combobox
	PredefinedGraphs();//preload
	return TRUE;
}

/*Function: [Event-Driven] Clicking on the view button will first clear the area of any remaining graphs, then will load up a graph as per the Combobox visible (comboGraphSelect_GH)*/
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
	this->zone = temp->unloadGraph();
}

/*Function: [Event-Driven] Brings up the Serialziation to store the information (looping through the graphs vector.*/
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

/*Function: [Event-Driven] Brings up the Serialzation when loading up a sample of graphs. */
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

/*Function: [Event-Driven] Brings up a MessageBox that displays helpful tips.*/
void CGraphDlg::OnBnClickedHelpGraph()
{
	MessageBox(L"Select a graph you wish to see from the delegated section.\nAfter that click on View to see it visually.\n\nIf you intend on viewing these in teh future, please save the graph by clicking on Save.\n\nTo view a old version of a graph click on Load and select the correct file.\nNOTE: Any progress from before will be cleared, best to save beforehand.\n\nEnjoy!");
	ClearGraphArea();
}

/*Function: [void] Clears a exact space of the dialog. */
void CGraphDlg::ClearGraphArea()
{
	InvalidateRect(zone, true);
}

/*Function: [void] Creates custom GraphObjects calling their CTORs and DisplayGraph functionality. Loading into the Vector.*/
void CGraphDlg::PredefinedGraphs()
{
	vector <int> information;
	vector <CString> legendValue;
	CClientDC pDC(this);
	GraphObject* graph;
	CString xAxis, yAxis;
	CPoint p(START_LINE_GRAPH_X, START_LINE_GRAPH_Y);
	yAxis = L"Amount\nof\nSick";
	
	loadFromMap(Counters.CountByHostital, information, legendValue, false);
	xAxis = L"Hospital Names";
	graph = new GraphObject(&pDC, p, information, legendValue, xAxis, yAxis);
	information.clear(); legendValue.clear();
	graph->displayGraph(true, &pDC);
	graphs.push_back(graph);
	this->zone = graph->unloadGraph();
	ClearGraphArea();

	loadFromMap(Counters.CountByArea, information, legendValue, false);
	xAxis = L"Area Type Names";
	graph = new GraphObject(&pDC, p, information, legendValue, xAxis, yAxis);
	information.clear(); legendValue.clear();
	graph->displayGraph(true, &pDC);
	graphs.push_back(graph);
	this->zone = graph->unloadGraph();
	ClearGraphArea();

	loadFromMap(Counters.CountByCity, information, legendValue, true);
	xAxis = L"City Names";
	graph = new GraphObject(&pDC, p, information, legendValue, xAxis, yAxis);
	information.clear(); legendValue.clear();
	graph->displayGraph(true, &pDC);
	graphs.push_back(graph);
	this->zone = graph->unloadGraph();
	ClearGraphArea();
	
	loadFromMap(Counters.CountByLevel, information, legendValue, false);
	xAxis = L"Sickness Levels";
	graph = new GraphObject(&pDC, p, information, legendValue, xAxis, yAxis);
	information.clear(); legendValue.clear();
	graph->displayGraph(true, &pDC);
	graphs.push_back(graph);
	this->zone = graph->unloadGraph();
	ClearGraphArea();

	information.push_back(Counters.TotalHospitalized);
	information.push_back(Counters.TotalNonHospitalized);
	information.push_back(Counters.TotalRecovered);
	information.push_back(Counters.TotalIsolated);
	legendValue.push_back(L"Total Hospitalized");
	legendValue.push_back(L"Total NonHospitalized");
	legendValue.push_back(L"Total Recovered");
	legendValue.push_back(L"Total Isolated");
	xAxis = L"Types of Added People";
	graph = new GraphObject(&pDC, p, information, legendValue, xAxis, yAxis);
	information.clear(); legendValue.clear();
	graph->displayGraph(true, &pDC);
	graphs.push_back(graph);
	this->zone = graph->unloadGraph();
	ClearGraphArea();
}

/*Function: [void] Gets a Map and loads the information of each counter map into the vectors. If sortMe is true it will sort the map and limit it to 20 items.*/
void CGraphDlg::loadFromMap(map<CString, int> &mMap, vector <int> &info, vector <CString> &legendValue, bool sortMe)
{
	map<CString, int>::iterator itr;//edit - sort the city map first, then load up to 20 items only.
	vector <pair<CString, int>> vec;
	pair <CString, int> par;
	for (itr = mMap.begin(); itr != mMap.end(); ++itr)
	{
		par.first = itr->first;
		par.second = itr->second;
		vec.push_back(par);
		legendValue.push_back(itr->first);
		info.push_back(itr->second);
	}
	if (sortMe)
	{
		std::sort(vec.begin(), vec.end());
		legendValue.clear();
		info.clear();
		int len = vec.size() > 20 ? vec.size() - 20 : 0;
		for (int i = len; i < vec.size(); i++)
		{
			legendValue.push_back(vec[i].first);
			info.push_back(vec[i].second);
		}
	}
}