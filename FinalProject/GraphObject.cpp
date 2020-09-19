// GraphObject.cpp : implementation file
//

#include "pch.h"
#include "FinalProject.h"
#include "GraphObject.h"
IMPLEMENT_SERIAL(GraphObject, CObject, 1)

GraphObject::GraphObject()
{
	this->pDC = nullptr;
	this->pStart.x = 0;
	this->pStart.y = 0;
	this->xAxisName = _T("NA_X");
	this->yAxisName = _T("NA_Y");
}

GraphObject::GraphObject(CClientDC* pDC, CPoint start, vector<int> info, vector<CString> legendValues, CString xAxis, CString yAxis)
{
	this->pDC = pDC;
	this->pStart = start;
	this->information = info;
	this->xAxisName = xAxis;
	this->yAxisName = yAxis;
	this->legendValues = legendValues;
}

GraphObject::~GraphObject()
{

}

void GraphObject::createAxis()
{
	CPoint po = pStart, aHead;
	SIZE s; s.cx = 150; s.cy = 20;
	unsigned int ahead_pad = 5;
	CPen* pen; CBrush* brush;
	brush = new CBrush(COLOR_BLACK);
	pen = new CPen(PS_SOLID, 3, COLOR_BLACK);
	pDC->SelectObject(pen);
	pDC->SelectObject(brush);

	//x axis line
	pDC->MoveTo(po);//start
	po.x += this->length + 15;
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
	//xaxis name
	CRect r = new CRect(po, s);
	pDC->DrawText(xAxisName, r, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_ENDELLIPSIS);

	pGraph_BR.y = po.y;

	//yaxis name
	s.cy = 60;
	po.x = pStart.x - s.cy;
	po.y = pStart.y - height / 2;
	r = new CRect(po, s);
	pDC->DrawText(yAxisName, r, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_ENDELLIPSIS);
	pGraph_TL.x = po.x;
}

void GraphObject::displayGraph()
{
	unsigned int i = 0;
	long max = -1;
	while (i < information.size())
	{
		if (information[i] > max) max = information[i];
		i++;
	}
	this->length = information.size() * 2 * 15;
	// *2 - Filler basically, a "Ghost" Rect then the actual Rect. 30 padding each.
	this->height = max;
	createAxis();
	createRectangles();
	createLegend();

}

void GraphObject::createRectangles()
{
	COLORREF ref;
	CRect rec, * r;
	CString val;
	CPoint st = this->pStart, end, po;
	SIZE s; s.cx = 25; s.cy = 15;
	CPen* pen; CBrush* brush;
	for (unsigned int i = 0; i < information.size(); i++)//drawing the rects
	{
		ref = generateRandomColor(0, 255);
		colors.push_back(ref);
		brush = new CBrush(ref);
		pen = new CPen(PS_SOLID, 1, ref);
		pDC->SelectObject(pen);
		pDC->SelectObject(brush);

		st.x += 15;
		end.x = st.x + 15;
		end.y = pStart.y - information[i];
		rec = new CRect(st, end);
		pDC->Rectangle(rec);
		rects.push_back(rec);

		val.Format(_T("%d"), information[i]);
		po = end; po.y -= s.cx; po.x -= s.cy;
		r = new CRect(po, s);
		pDC->DrawText(val, r, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_ENDELLIPSIS);

		st.x += 15;
		DeleteObject(pen);
		DeleteObject(brush);
		DeleteObject(r);
	}
}

void GraphObject::createLegend()
{
	SIZE s, sq_s; s.cx = 150; s.cy = 20; sq_s.cx = 15; sq_s.cy = 15;
	CPoint q, pos;// = pGraph_BL;
	pos.y = pGraph_BR.y + 40; pos.x = pGraph_TL.x + 20;
	CRect* r, sq;
	unsigned int i = 0, keep = pos.y, low = 0;
	CPen* pen; CBrush* brush;

	while (i < legendValues.size())
	{

		r = new CRect(pos, s);
		pDC->DrawText(legendValues[i], r, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_ENDELLIPSIS);

		brush = new CBrush(colors[i]);
		pen = new CPen(PS_SOLID, 1, colors[i]);
		pDC->SelectObject(pen);
		pDC->SelectObject(brush);
		q = pos; q.x -= 20;
		sq = new CRect(q, sq_s);
		pDC->Rectangle(sq);

		i++;
		pos.y += s.cy;
		if (i % 5 == 0) {
			pos.x += s.cx; low = pos.y;  pos.y = keep;
		}
		DeleteObject(r);
		DeleteObject(sq);
	}
	pGraph_BR.y = pos.y > low ? pos.y + s.cy : low + s.cy;
	pGraph_BR.x = pos.x > length ? pos.x + s.cx : length + s.cx;
}

void GraphObject::loadExistingGraph(CClientDC* _pDC)
{
	//Logically we come here when everything is set. The Data is here, no need to push items into anything.
	//createAxis and createLegend both do not pushback data, meaning this function will "redo" what createRectangle does.
	//note: colors, nameValues, information vectors are all the same size.
	CString val;
	SIZE s; s.cx = 25; s.cy = 15;
	CPoint pos;
	CRect* r, temp;
	CPen* pen; CBrush* brush;
	this->pDC = _pDC;

	createAxis();

	for (unsigned int i = 0; i < information.size(); i++)
	{
		temp = rects[i];

		brush = new CBrush(colors[i]);
		pen = new CPen(PS_SOLID, 1, colors[i]);
		pDC->SelectObject(pen);
		pDC->SelectObject(brush);
		pDC->Rectangle(temp);

		val.Format(_T("%d"), information[i]);
		pos.y = temp.bottom; pos.x = temp.left;  pos.y -= s.cy * 2;//temp.bottom cause the rectangle is flipped due to the nature of it all. top will always point to 450 which is the base line of ours.
		r = new CRect(pos, s);
		pDC->DrawText(val, r, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_ENDELLIPSIS);

		DeleteObject(r);
		DeleteObject(pen);
		DeleteObject(brush);
	}

	createLegend();
}

CRect GraphObject::unloadGraph()
{
	return new CRect(pGraph_TL, pGraph_BR);
}


COLORREF GraphObject::generateRandomColor(int min, int max) //range : [min, max)
{

	int val[3];
	static bool first = true;
	if (first)
	{
		srand(time(NULL)); //seeding for the first time only!
		first = false;
	}

	for (int i = 0; i < 3; i++) val[i] = min + rand() % ((max + 1) - min);
	COLORREF ref(RGB(val[0], val[1], val[2]));
	return ref;
}


void GraphObject::Serialize(CArchive& archive)
{
	CObject::Serialize(archive);

	if (archive.IsStoring()) {
		archive << pStart << pGraph_TL << pGraph_BR << height << length << xAxisName << yAxisName; //<< information << legendValues << colors << rects
		saveIntoArchive(information, archive, information.size());
		saveIntoArchive(legendValues, archive, legendValues.size());
		saveIntoArchive(colors, archive, colors.size());
		saveIntoArchive(rects, archive, information.size());
	}
	else
	{
		archive >> pStart >> pGraph_TL >> pGraph_BR >> height >> length >> xAxisName >> yAxisName;
		loadFromArchive(information, archive, information.size());
		loadFromArchive(legendValues, archive, legendValues.size());
		loadFromArchive(colors, archive, colors.size());
		loadFromArchive(rects, archive, information.size());
	}
}

template<class STLVectorType>
void GraphObject::saveIntoArchive(vector<STLVectorType>& ctype, CArchive& arc, size_t size)
{
	arc << (int)size;
	for (size_t i = 0; i < size; i++)
	{
		arc << ctype[i];
	}
}

template<class STLVectorType>
void GraphObject::loadFromArchive(vector<STLVectorType>& ctype, CArchive& arc, size_t size)
{
	arc >> size;
	ctype.resize(size);
	for (size_t i = 0; i < size; i++)
	{
		arc >> ctype[i];
	}
}

