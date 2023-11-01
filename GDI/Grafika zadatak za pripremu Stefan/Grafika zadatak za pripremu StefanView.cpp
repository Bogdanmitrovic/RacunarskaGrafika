
// Grafika zadatak za pripremu StefanView.cpp : implementation of the CGrafikazadatakzapripremuStefanView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Grafika zadatak za pripremu Stefan.h"
#endif

#include "Grafika zadatak za pripremu StefanDoc.h"
#include "Grafika zadatak za pripremu StefanView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGrafikazadatakzapripremuStefanView

IMPLEMENT_DYNCREATE(CGrafikazadatakzapripremuStefanView, CView)

BEGIN_MESSAGE_MAP(CGrafikazadatakzapripremuStefanView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGrafikazadatakzapripremuStefanView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CGrafikazadatakzapripremuStefanView construction/destruction

CGrafikazadatakzapripremuStefanView::CGrafikazadatakzapripremuStefanView() noexcept
{
	// TODO: add construction code here

}

CGrafikazadatakzapripremuStefanView::~CGrafikazadatakzapripremuStefanView()
{
}

BOOL CGrafikazadatakzapripremuStefanView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGrafikazadatakzapripremuStefanView drawing

void CGrafikazadatakzapripremuStefanView::OnDraw(CDC* pDC)
{
	CGrafikazadatakzapripremuStefanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CPen zutaOlovkaDebela(PS_SOLID, 3, RGB(255, 255, 0));
	CPen zutaOlovkaTanka(PS_SOLID, 2, RGB(255, 255, 0));
	CPen* staraOlovka = pDC->SelectObject(&zutaOlovkaDebela);
	CBrush brushRoze(RGB(255, 50, 255));
	CBrush brushZuta(RGB(255, 255, 0));
	CBrush brushLjubicasta(RGB(150, 0, 200));
	CBrush brushZelena(RGB(50, 255, 0));
	CBrush brushCrvena(RGB(255, 0, 0));
	CBrush brushSablon(HS_VERTICAL, RGB(200, 200, 255));
	CBrush brushNarandzasta(RGB(200, 150, 10));
	CBrush* staraChetka = pDC->SelectObject(&brushRoze);

	POINT points1[3] = { 
		CPoint(25,150),
		CPoint(125,150),
		CPoint(125,50) };
	pDC->Polygon(points1, 3);

	pDC->SelectObject(&brushZuta);
	POINT points2[4] = {
		CPoint(25,150),
		CPoint(175,150),
		CPoint(250,225),
		CPoint(100,225)
	};
	pDC->Polygon(points2, 4);

	pDC->SelectObject(&brushLjubicasta);
	POINT points3[4] = {
		CPoint(175,150),
		CPoint(250,75),
		CPoint(325,150),
		CPoint(250,225)
	};
	pDC->Polygon(points3, 4);

	pDC->SelectObject(&brushZelena);
	POINT points4[3] = {
		CPoint(400,75),
		CPoint(250,75),
		CPoint(325,150)
	};
	pDC->Polygon(points4, 3);

	pDC->SelectObject(&brushCrvena);
	POINT points5[3] = {
		CPoint(400,75),
		CPoint(500,175),
		CPoint(300,175)
	};
	pDC->Polygon(points5, 3);

	pDC->SelectObject(&brushSablon);
	POINT points6[3] = {
		CPoint(500,175),
		CPoint(500,375),
		CPoint(300,175)
	};
	pDC->Polygon(points6, 3);

	pDC->SelectObject(&brushNarandzasta);
	POINT points7[3] = {
		CPoint(300,425),
		CPoint(425,300),
		CPoint(300,175)
	};
	pDC->Polygon(points7, 3);

	pDC->SelectObject(&zutaOlovkaTanka);
	pDC->SelectStockObject(HOLLOW_BRUSH);
	DrawRegularPolygon(pDC, 100, 110, 7, 15, 0);
	DrawRegularPolygon(pDC, 325, 110, 8, 15, 3.14159 / 4);
	DrawRegularPolygon(pDC, 400, 135, 6, 20, 0);
	// i tako dalje svi ostali poligoni na istu foru
}

void CGrafikazadatakzapripremuStefanView::DrawRegularPolygon(CDC* pDC, int cx, int cy, int n, int r, float rotAngle)
{
	POINT* points = new POINT[n];
	float step = 2 * 3.14159 / n, angle = rotAngle;

	for (int i = 0; i < n; i++, angle += step)
	{
		points[i].x = cx + r * cos(angle);
		points[i].y = cy + r * sin(angle);
	}

	pDC->Polygon(points, n);
	delete[] points;
}
void CGrafikazadatakzapripremuStefanView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGrafikazadatakzapripremuStefanView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CGrafikazadatakzapripremuStefanView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGrafikazadatakzapripremuStefanView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CGrafikazadatakzapripremuStefanView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGrafikazadatakzapripremuStefanView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGrafikazadatakzapripremuStefanView diagnostics

#ifdef _DEBUG
void CGrafikazadatakzapripremuStefanView::AssertValid() const
{
	CView::AssertValid();
}

void CGrafikazadatakzapripremuStefanView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGrafikazadatakzapripremuStefanDoc* CGrafikazadatakzapripremuStefanView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGrafikazadatakzapripremuStefanDoc)));
	return (CGrafikazadatakzapripremuStefanDoc*)m_pDocument;
}
#endif //_DEBUG