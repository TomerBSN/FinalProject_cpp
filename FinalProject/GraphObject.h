#pragma once
#include <vector>
#define COLOR_BLACK 0xFFFFFFFF
#define UPPERBOUND 400
#define LOWERBOUND 10
#define MAXLEGEND 20

using namespace std;
// GraphObject command target

class GraphObject : public CObject
{
	DECLARE_SERIAL(GraphObject)
public:
	GraphObject();//Must have
	GraphObject(CClientDC* pDC, CPoint start, vector<int> info, vector<CString> legendValues, CString xAxis, CString yAxis);
	virtual ~GraphObject();
	void createAxis();
	void displayGraph(bool generateNew, CClientDC* _pDC);
	void createDataVectors();
	void createLegend(unsigned int mod);
	void loadGraph();
	//the main function, draws it all
	CRect unloadGraph();
	void AdjustAllRects(bool adj);
	void Serialize(CArchive& archive);//To be edited
	COLORREF generateRandomColor(int min, int max);

	template <class STLVectorType>
	void  saveIntoArchive(vector<STLVectorType>& ctype, CArchive& arc, size_t size);
	template <class STLVectorType>
	void  loadFromArchive(vector<STLVectorType>& ctype, CArchive& arc, size_t size);

private:
	CClientDC* pDC = nullptr;//holds my "Drawing Assistant" so I can always refer to the OnPaint of the Graph Dialog
	CPoint pStart, pGraph_TL, pGraph_BR; //pStart is the bottom left point of the graph, that way I know where to start it all; pGraph points are total edges of the graph itself. 
	long height, length; //holds my max hieght and length, then uses the bigger of the two. Good for Axis.
	CString xAxisName, yAxisName; //Each graph is different so now I am using these CStrings to create a name for the axis
	vector <int> information; //holds all the info I need to represent. It will be the heights of each Rectangle.
	vector <CString> legendValues; //will hold the names of the items we are given for the legend area. 
	vector <COLORREF> colors; // will hold the values of each color in the rectangles. 
	vector <CRect> rects; //holds each rectangle drawn, specifically their location.
};

