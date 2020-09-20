#pragma once
#include "afxdialogex.h"
#include "FinalProjectDlg.h"
#include "GraphObject.h"
#include "Global.h"

#define START_LINE_GRAPH_Y 400
#define START_LINE_GRAPH_X 90
// CGraphDlg dialog

class CGraphDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGraphDlg)

public:
	CGraphDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CGraphDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPH_DIALOG };
#endif
private:
	CRect zone; //Holds the area of the Graph itself, getting the details from GraphObject::unloadGraph
	vector<CObject*>graphs; //Holds all the graphs
	size_t graphs_size = 0; //Holds the size of the graphs vector.
	CComboBox comboGraphsSelect_GH_Controller; //Controls the Graph Selection Combobox
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	void OnBnClickedViewGraph();
	afx_msg void OnBnClickedSaveGraphs();
	afx_msg void OnBnClickedLoadGraphs();
	afx_msg void OnBnClickedHelpGraph();
	void ClearGraphArea();
	void PredefinedGraphs();
	void loadFromMap(map<CString, int>& mMap, vector<int>& info, vector<CString>& legendValue, bool sortMe);

};
