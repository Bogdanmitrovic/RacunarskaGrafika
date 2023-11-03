
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
	CPen nullpen(PS_NULL, 1, RGB(0, 0, 0));
	CPen pen1(PS_SOLID, 5, RGB(0, 0, 255));
	CPen pen2(PS_SOLID, 2, RGB(0, 0, 255));
	CPen penGrid(PS_SOLID, 1, RGB(255, 255, 255));
	CPen* oldPen = pDC->SelectObject(&nullpen);

	CBrush grey(RGB(200,200,200));
	CBrush green(RGB(0, 255, 0));
	CBrush yellow(RGB(255, 255, 0));
	CBrush orange(RGB(255, 165, 0));
	CBrush purple(RGB(138, 43, 226));
	CBrush red(RGB(255, 0, 0));
	CBrush pink(RGB(255, 0, 255));
	CBrush pattern(HS_CROSS, RGB(0, 0, 255));
	CBrush* oldBrush = pDC->SelectObject(&grey);

	pDC->Rectangle(0, 0, 500, 500);

	pDC->SelectObject(pen1);
	POINT pts1[3] = {
		CPoint(75,250),
		CPoint(300,250),
		CPoint(300,25)
	};
	pDC->SelectObject(green);
	pDC->Polygon(pts1, 3);

	POINT pts2[3] = {
		CPoint(75,250),
		CPoint(300,250),
		CPoint(300,475)
	};
	pDC->SelectObject(yellow);
	pDC->Polygon(pts2, 3);

	POINT pts3[3] = {
		CPoint(300,250),
		CPoint(300,25),
		CPoint(425,137)
	};
	pDC->SelectObject(purple);
	pDC->Polygon(pts3, 3);

	POINT pts4[3] = {
		CPoint(300,25),
		CPoint(425,25),
		CPoint(425,137)
	};
	pDC->SelectObject(orange);
	pDC->Polygon(pts4, 3);

	POINT pts5[4] = {
		CPoint(425,137),
		CPoint(425,250),
		CPoint(300,367),
		CPoint(300,250)
	};
	pDC->SelectObject(red);
	pDC->Polygon(pts5, 4);

	POINT pts6[3] = {
		CPoint(425,250),
		CPoint(425,367),
		CPoint(300,367)
	};
	pDC->SelectObject(pink);
	pDC->Polygon(pts6, 3);

	pDC->SelectObject(pattern);
	pDC->Rectangle(300, 367, 425, 475);

	pDC->SelectStockObject(HOLLOW_BRUSH);
	pDC->SelectObject(pen2);
	DrawRegularPolygon(pDC, 675 / 3, 525 / 3, 37, 4, 0);
	DrawRegularPolygon(pDC, 675 / 3, 975 / 3, 37, 5, 5*3.14 / 6);
	DrawRegularPolygon(pDC, 1150 / 3, 187 / 3, 18, 8, 3.14 / 6);
	
	if (gridEnabled)
	{
		pDC->SelectObject(penGrid);
		for (int i = 25; i <= 500; i += 25)
		{
			pDC->MoveTo(CPoint(i, 0));
			pDC->LineTo(CPoint(i, 500));
			pDC->MoveTo(CPoint(0, i));
			pDC->LineTo(CPoint(500, i));
		}
	}

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
}

void CGrafikazadatakzapripremuStefanView::DrawRegularPolygon(CDC* pDC, int cx, int cy, int r, int n, float rotAngle)
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


// CV5View message handlers


void CV5View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonUp(nFlags, point);
	gridEnabled = !gridEnabled;
	Invalidate();
}
