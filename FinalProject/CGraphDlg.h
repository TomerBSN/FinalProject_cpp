#pragma once
#include "afxdialogex.h"
#include "FinalProjectDlg.h"
#include "GraphObject.h"
#include "Global.h"

#define START_LINE_GRAPH_Y 425
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
	CRect zone;
	vector<CObject*>graphs;
	size_t graphs_size = 0;
	CComboBox comboGraphsSelect_GH_Controller;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	void OnBnClickedViewGraph();
	afx_msg void OnBnClickedSaveGraphs();
	afx_msg void OnBnClickedLoadGraphs();
	afx_msg void OnBnClickedHelpGraph();
	//afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void ClearGraphArea();
	void PredefinedGraphs();

	void loadFromMap(map<CString, int>& mMap, vector<int>& info, vector<CString>& legendValue);
	void adjustScrollBar(GraphObject& grph);
	CScrollBar srGraphScroll_Controller;
	
};
