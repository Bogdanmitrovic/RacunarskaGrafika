
// kaktusView.cpp : implementation of the CkaktusView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "kaktus.h"
#endif

#include "kaktusDoc.h"
#include "kaktusView.h"
constexpr auto GRIDSIZE = 25;
#define TO_RAD(x) (x*3.14159/180)
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

constexpr auto CENTAR_X = 250;
constexpr auto CENTAR_Y = 425;

#define DEBLJINA 60


// CkaktusView

IMPLEMENT_DYNCREATE(CkaktusView, CView)

BEGIN_MESSAGE_MAP(CkaktusView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CkaktusView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CkaktusView construction/destruction

CkaktusView::CkaktusView() noexcept
{
	grid = false;
	angle1 = 0;
	angle2 = 0;
}

CkaktusView::~CkaktusView()
{
}

BOOL CkaktusView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or style(s here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CkaktusView drawing

void CkaktusView::OnDraw(CDC* pDC)
{
	CkaktusDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	CPen gridPen(PS_SOLID, 1, RGB(255, 255, 255));

	CBrush pozadina(RGB(137, 207, 240));
	CPen hollow(PS_NULL, 1, RGB(0, 0, 0));

	pDC->SelectObject(pozadina);
	pDC->SelectObject(hollow);
	pDC->Rectangle(0, 0, 500, 500);

	DrawText(pDC, 30, "Stefan Smiljic, 18379", 477, 152, 90, RGB(0, 0, 0));
	DrawText(pDC, 30, "Stefan Smiljic, 18379", 475, 150, 90, RGB(255, 255, 0));

	DrawFigure(pDC);
	DrawSaksija(pDC);

	if (grid)
	{
		pDC->SelectObject(gridPen);
		pDC->SelectStockObject(HOLLOW_BRUSH);
		for (int i = GRIDSIZE; i < 500; i += GRIDSIZE)
		{
			pDC->MoveTo(0, i); pDC->LineTo(500, i);
			pDC->MoveTo(i, 0); pDC->LineTo(i, 500);
		}
	}
}
void CkaktusView::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM xForm{};
	xForm.eM11 = 1.0;
	xForm.eM12 = 0.0;
	xForm.eM21 = 0.0;
	xForm.eM22 = 1.0;
	xForm.eDx = dX;
	xForm.eDy = dY;

	pDC->ModifyWorldTransform(&xForm, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CkaktusView::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
{
	XFORM xForm{};
	xForm.eM11 = sX;
	xForm.eM12 = 0.0;
	xForm.eM21 = 0.0;
	xForm.eM22 = sY;
	xForm.eDx = 0.0;
	xForm.eDy = 0.0;

	pDC->ModifyWorldTransform(&xForm, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CkaktusView::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM xForm{};
	xForm.eM11 = cos(angle);
	xForm.eM12 = sin(angle);
	xForm.eM21 = -sin(angle);
	xForm.eM22 = cos(angle);
	xForm.eDx = 0.0;
	xForm.eDy = 0.0;

	pDC->ModifyWorldTransform(&xForm, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CkaktusView::DrawText(CDC* pDC, int size, char* text, int x, int y, int degrees, COLORREF color)
{
	
	CFont font1;
	font1.CreateFont(size, 0, degrees*(-10), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");
	CFont* oldFont = pDC->SelectObject(&font1);
	int oldFontColor = pDC->SetTextColor(color);
	int oldTextAlign = pDC->SetTextAlign(TA_LEFT);
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);

	pDC->TextOut(x, y-size/2, (CString)text);

	pDC->SetTextColor(oldFontColor);
	pDC->SetTextAlign(oldTextAlign);
	pDC->SetBkMode(oldBkMode);
	pDC->SelectObject(oldFont);
	font1.DeleteObject();
}

void CkaktusView::DrawSaksija(CDC* pDC)
{
	POINT pts[8] = {
		CPoint(191, 428),
		CPoint(312, 428),
		CPoint(312, 449),
		CPoint(302, 449),
		CPoint(292, 499),
		CPoint(211, 499),
		CPoint(201, 449),
		CPoint(191, 449)
	};

	CBrush brush(RGB(158, 82, 63));
	CBrush* oldBrush = pDC->SelectObject(&brush);
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&pen);

	pDC->Polygon(pts, 8);
	pDC->MoveTo(201, 449); pDC->LineTo(302, 449);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
}

void CkaktusView::DrawFigure(CDC* pDC)
{
	HENHMETAFILE svetlo = GetEnhMetaFile(_T("cactus_part_light.emf"));
	HENHMETAFILE tamno = GetEnhMetaFile(_T("cactus_part.emf"));
	if (svetlo == NULL || tamno == NULL)
		return;

	int prevMode = pDC->SetGraphicsMode(GM_ADVANCED);

	KaktusKomad(pDC, &svetlo, 250, 387, 60, 75, angle1, 0);
	KaktusKomad(pDC, &svetlo, 304, 262, 40, 75, angle1, 0, angle2);
	KaktusKomad(pDC, &tamno, 198, 183, 60, 75, angle1, 0);
	KaktusKomad(pDC, &tamno, 198, 259, 40, 75, angle1, 0);
	KaktusKomad(pDC, &tamno, 275, 325, 20, 75, angle1, 45);
	KaktusKomad(pDC, &tamno, 250, 312, 20, 75, angle1, 0);
	KaktusKomad(pDC, &tamno, 225, 325, 20, 75, angle1, -45);
	KaktusKomad(pDC, &tamno, 163, 300, 40, 75, angle1, -90);
	KaktusKomad(pDC, &tamno, 344, 300, 40, 75, angle1, 90);
	KaktusKomad(pDC, &tamno, 408, 271, 40, 75, angle1, 45);
	KaktusKomad(pDC, &tamno, 408, 324, 40, 75, angle1, 135);

	CvorKomad(pDC, 250, 350, angle1);
	CvorKomad(pDC, 200, 300, angle1);
	CvorKomad(pDC, 199, 223, angle1);
	CvorKomad(pDC, 305, 300, angle1);
	CvorKomad(pDC, 380, 300, angle1);
	CvorKomad(pDC, 250, 425, angle1);
	pDC->SetGraphicsMode(prevMode);
}

void CkaktusView::KaktusKomad(CDC* pDC, HENHMETAFILE* tekstura, int x1, int y1, int sirina, int visina, int ugaoOkoCentraRotacije, int ugaoOkoSebe, int ugao2)
{
	XFORM xFormOld;
	pDC->GetWorldTransform(&xFormOld);

	sirina >>= 1; //ovo se deli da bi se vrtelo oko onu tacku dole a ne oko svoj centar
	visina >>= 1;

	Rotate(pDC, TO_RAD(ugaoOkoSebe), true);
	if (ugao2 != 0)
	{
		Translate(pDC, 0, -visina, true);
		Rotate(pDC, TO_RAD(ugao2), true);
		Translate(pDC, 0, visina, true);//s ovaj ugao podesavamo onaj malecak kaktus
	}
	Translate(pDC, x1 - CENTAR_X, y1 - CENTAR_Y, true);
	Rotate(pDC, TO_RAD(ugaoOkoCentraRotacije), true);
	Translate(pDC, CENTAR_X, CENTAR_Y, true);

	
	pDC->PlayMetaFile(*tekstura, CRect(-sirina, -visina, sirina, visina));
	pDC->SetWorldTransform(&xFormOld);
}

void CkaktusView::CvorKomad(CDC* pDC, int x1, int y1, int ugaoOkoCentraRotacije)
{
	XFORM xFormOld;
	pDC->GetWorldTransform(&xFormOld);

	CBrush brush(RGB(0, 204, 0));
	CBrush* oldBrush = pDC->SelectObject(&brush);
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&pen);

	Translate(pDC, x1 - CENTAR_X, y1 - CENTAR_Y, true);
	Rotate(pDC, TO_RAD(ugaoOkoCentraRotacije), true);
	Translate(pDC, CENTAR_X, CENTAR_Y, true);
	pDC->Ellipse(-10, -10, 10, 10);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);

	pDC->SetWorldTransform(&xFormOld);
}

void CkaktusView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CkaktusView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CkaktusView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CkaktusView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CkaktusView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CkaktusView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CkaktusView diagnostics

#ifdef _DEBUG
void CkaktusView::AssertValid() const
{
	CView::AssertValid();
}

void CkaktusView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CkaktusDoc* CkaktusView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CkaktusDoc)));
	return (CkaktusDoc*)m_pDocument;
}
#endif //_DEBUG


// CkaktusView message handlers


void CkaktusView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	switch (nChar)
	{
		case 'G':grid = !grid; break;
		case 'A': angle1 -= 6; break;
		case 'D': angle1 += 6; break;
		case 'W': angle2 -= 6; break;
		case 'S': angle2 += 6; break;
		default: return;
	}
	Invalidate();
}

BOOL CkaktusView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CView::OnEraseBkgnd(pDC);
}
