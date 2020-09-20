// GraphObject.cpp : implementation file
//

#include "pch.h"
#include "FinalProject.h"
#include "GraphObject.h"
IMPLEMENT_SERIAL(GraphObject, CObject, 1)

//Function: [CTOR] Generic CTor, needed for the Serialization.
GraphObject::GraphObject()
{
	this->pDC = nullptr;
	this->pStart.x = 0;
	this->pStart.y = 1;
	this->xAxisName = _T("NA_X");
	this->yAxisName = _T("NA_Y");
}

//Function: [CTOR] A Custom CTOR that will load up all that is needed. Specifically need pDC to paint on the dialog.
GraphObject::GraphObject(CClientDC* pDC, CPoint start, vector<int> info, vector<CString> legendValues, CString xAxis, CString yAxis)
{
	this->pDC = pDC;
	this->pStart = start;
	this->information = info;
	this->xAxisName = xAxis;
	this->yAxisName = yAxis;
	this->legendValues = legendValues;
}

//Function; [DTOR] Generic destructor
GraphObject::~GraphObject()
{

}

/*
Function: [void] A linear function that creates lines, moving them back and forth upon the pDC. Will also add the Axis's names.
*/
void GraphObject::createAxis()
{
	CPoint po = pStart, aHead;
	SIZE s; s.cx = 250; s.cy = 30;
	unsigned int ahead_pad = 5;
	CPen* pen; CBrush* brush;
	brush = new CBrush(COLOR_BLACK);
	pen = new CPen(PS_SOLID, 3, COLOR_BLACK);
	pDC->SelectObject(pen);
	pDC->SelectObject(brush);

	//x axis line
	pDC->MoveTo(po);//start
	po.x += this->length+10;
	pDC->LineTo(po);//end
	//XAxis Arrow Head;
	aHead = po;
	pDC->MoveTo(aHead);
	po.x -= ahead_pad; po.y -= ahead_pad;
	pDC->LineTo(po);
	pDC->MoveTo(aHead);
	po.y += ahead_pad * 2;
	pDC->LineTo(po);

	//y axis line
	po = pStart;
	pDC->MoveTo(po);//start
	po.y -= this->height + s.cy;
	pDC->LineTo(po);//end
	//yAxis Arrow Head
	aHead = po;
	pDC->MoveTo(aHead);
	po.x -= ahead_pad; po.y += ahead_pad;
	pDC->LineTo(po);
	pDC->MoveTo(aHead);
	po.x += ahead_pad * 2;
	pDC->LineTo(po);

	pGraph_TL.y = po.y - s.cy;
	po = pStart;
	po.y += s.cy;

	CFont font;
	font.CreatePointFont(95, _T("Arial"));
	pDC->SelectObject(&font);
	//xaxis name
	CRect r = new CRect(po, s);
	pDC->DrawText(xAxisName, r, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_ENDELLIPSIS);

	pGraph_BR.y = po.y;

	//yaxis name
	s.cy = 70;
	po.x = pStart.x - s.cy;
	po.y = pStart.y - height / 2;
	r = new CRect(po, s);
	pDC->DrawText(yAxisName, r, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_ENDELLIPSIS);
	pGraph_TL.x = po.x;
}

/*
Function: [void] A function taht gets the CDC and a bool to see if its a new graph being made or not. If it is, it calls for createDataVector that loads up the Colors, Rects to be created. It will also loop through some things and adjust them if needed, and if generateNew is false, it will call the axis, then the rectangles, then the legend to be created.
*/
void GraphObject::displayGraph(bool generateNew, CClientDC* _pDC)
{
	unsigned int mod = 5;
	int max = -1;
	for (unsigned int i = 0; i < information.size(); i++) {
		if (information[i] > max) max = information[i];
		if (information[i] < 0) information[i] *= -1;
	}

	if (generateNew == true)
		createDataVectors();

	this->length = information.size() * 2 * 15;
	this->height = (long)max;

	if (max > UPPERBOUND)
	{
		AdjustAllRects(true);
		this->height = (long)max / 3;
	}

	else if (max <= LOWERBOUND)
	{
		//AdjustAllRects(false);
		this->height = 50;
	}

	if (information.size() > MAXLEGEND)
		mod = 10;

	this->pDC = _pDC;
	createAxis();
	createLegend(mod);
	loadGraph();
}

/*
Function: [void] Loops through the information we have gotten in the CTOR and pre-generates the RECTS and COLORS vetors, loading them up for use later. This is only called if the generateNew bool from the displayGraph is called.
*/
void GraphObject::createDataVectors()
{
	COLORREF ref;
	CRect rec;
	CPoint st = this->pStart, end, po;
	for (unsigned int i = 0; i < information.size(); i++)//drawing the rects
	{
		ref = generateRandomColor(0, 255);
		colors.push_back(ref);

		st.x += 15;
		end.x = st.x + 15;
		end.y = pStart.y - information[i] - 2;
		rec = new CRect(st, end);
		rects.push_back(rec);
		st.x += 15;
	}
}

/*
Function: [void] Creates the names on the bottom of the graph; the mod is to see how many names will be listed under each other (Noramlly 5 or 10).
*/
void GraphObject::createLegend(unsigned int mod)
{
	SIZE s, sq_s; s.cx = 150; s.cy = 20; sq_s.cx = 15; sq_s.cy = 15;
	CPoint q, pos;// = pGraph_BL;
	pos.y = pGraph_BR.y + 50; pos.x = pGraph_TL.x + 50;
	CRect* r, sq;
	unsigned int i = 0, keep = pos.y, low = 0;
	CPen* pen; CBrush* brush;
	CString tstr;
	while (i < legendValues.size())
	{
		tstr.Format(_T("%d. %s"), i, (LPCTSTR)legendValues[i]);
		r = new CRect(pos, s);
		CFont font;
		font.CreatePointFont(95, _T("Arial"));
		pDC->SelectObject(&font);
		pDC->DrawText(tstr, r, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_ENDELLIPSIS);

		brush = new CBrush(colors[i]);
		pen = new CPen(PS_SOLID, 1, colors[i]);
		pDC->SelectObject(pen);
		pDC->SelectObject(brush);
		q = pos; q.x -= 20;
		sq = new CRect(q, sq_s);
		pDC->Rectangle(sq);

		i++;
		pos.y += s.cy;

		if (i % mod == 0)
		{
			pos.x += s.cx;
			low = pos.y;
			pos.y = keep;
		}

		DeleteObject(r);
		DeleteObject(sq);
	}
	pGraph_BR.y = pos.y > low ? pos.y + s.cy : low + s.cy;
	pGraph_BR.x = pos.x > length ? pos.x + s.cx : length + s.cx;
}

/*
Function: [void] Loads the Graph onto the screen with all the data already in it. Make note that the colors,information,rects are all the same length no matter what.
*/
void GraphObject::loadGraph()
{
	CString val;
	SIZE s; s.cx = 30; s.cy = 25;
	CPoint pos;
	CRect* r, temp;
	CPen* pen; CBrush* brush;

	for (unsigned int i = 0; i < information.size(); i++)
	{
		temp = rects[i];

		brush = new CBrush(colors[i]);
		pen = new CPen(PS_SOLID, 1, colors[i]);
		pDC->SelectObject(pen);
		pDC->SelectObject(brush);
		pDC->Rectangle(temp);
		val.Format(_T("%d"), information[i]);
		pos.y = temp.bottom; pos.x = temp.left;  pos.y -= s.cy;//temp.bottom cause the rectangle is flipped due to the nature of it all. top will always point to 450 which is the base line of ours.
		r = new CRect(pos, s);
		CFont font;
		font.CreatePointFont(95, _T("Arial"));
		pDC->SelectObject(&font);
		pDC->DrawText(val, r, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_ENDELLIPSIS);
		pos.y = pStart.y + 2; pos.x = temp.left;//  pos.y += s.cy/3;
		r = new CRect(pos, s);
		val.Format(_T("%d"), i);
		pDC->SelectObject(&font);
		pDC->DrawText(val, r, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_ENDELLIPSIS);
		DeleteObject(r);
		DeleteObject(pen);
		DeleteObject(brush);
	}
}

/*
Function: [CRect] Returns the actual size of the Graph to be "erased"; returning a CRect for it (use for InvalidateRect())
*/
CRect GraphObject::unloadGraph()
{
	return new CRect(pGraph_TL, pGraph_BR);
}

/*
Function: [void] Adjusts the Rects, deflating it if needed; if it is true it will lower the size of the rectangles by /3, if true it will let them raise by *10.
*/
void GraphObject::AdjustAllRects(bool adj)
{
	SIZE def;
	int _slimDown = 3;
	int _slimUp = 10;
	for (unsigned int i = 0; i < rects.size(); ++i)
	{
		def = rects[i].Size();
		def.cy = (adj) ? (def.cy / _slimDown) : (def.cy * _slimUp);
		rects[i].DeflateRect(def);
	}
}

/*Function: [COLORREF] Generates a random color via creating random ints and placing them into a RGB*/
COLORREF GraphObject::generateRandomColor(int min, int max) //range : [min, max)
{
	int val[3];
	static bool first = true;
	if (first)
	{
		srand(time(NULL)); //seeding for the first time only!
		first = false;
	}

	for (int i = 0; i < 3; i++)
		val[i] = min + rand() % ((max + 1) - min);

	COLORREF ref(RGB(val[0], val[1], val[2]));
	return ref;
}

/*Function: [void] The simplistic Serialize, gets a CArchive and then adds the current stream of bytes from the GraphObject. We need to call in saveIntoArchive or loadFromArchive for the vectors.*/
void GraphObject::Serialize(CArchive& archive)
{
	CObject::Serialize(archive);

	if (archive.IsStoring()) {
		archive << pStart << pGraph_TL << pGraph_BR << height << length << xAxisName << yAxisName;
		saveIntoArchive(information, archive, information.size());
		saveIntoArchive(legendValues, archive, legendValues.size());
		saveIntoArchive(colors, archive, colors.size());
		saveIntoArchive(rects, archive, information.size());
	}
	else//does not save properly, so when i load a vector it is sie 0 which is wrong..
	{
		archive >> pStart >> pGraph_TL >> pGraph_BR >> height >> length >> xAxisName >> yAxisName;
		loadFromArchive(information, archive, information.size());
		loadFromArchive(legendValues, archive, legendValues.size());
		loadFromArchive(colors, archive, colors.size());
		loadFromArchive(rects, archive, information.size());
	}
}

/*Function: [void] Gets a vector of any kind due to the template and loops through it, saving the size first, then each item until the end. */
template<class STLVectorType>
void GraphObject::saveIntoArchive(vector<STLVectorType>& ctype, CArchive& arc, size_t size)
{
	arc << size;
	for (size_t i = 0; i < size; i++)
		arc << ctype[i];
}

/*Function: [void] gets any vector due to the template, then loads up the size first, then loads all the data into the CArchive. */
template<class STLVectorType>
void GraphObject::loadFromArchive(vector<STLVectorType>& ctype, CArchive& arc, size_t size)
{
	arc >> size;
	ctype.resize(size);
	for (size_t i = 0; i < size; i++)
		arc >> ctype[i];
}