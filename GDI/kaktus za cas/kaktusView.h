
// kaktusView.h : interface of the CkaktusView class
//

#pragma once




class CkaktusView : public CView
{
protected: // create from serialization only
	CkaktusView() noexcept;
	DECLARE_DYNCREATE(CkaktusView)

// Attributes
public:
	CkaktusDoc* GetDocument() const;
	bool grid;
	int angle1;
	int angle2;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* DC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void DrawFigure(CDC* pDC);
	void KaktusKomad(CDC* pDC, HENHMETAFILE* tekstura, int x1, int y1, int sirina, int visina, int ugaoOkoCentraRotacije, int ugaoOkoSebe, int ugao2 = 0);
	void CvorKomad(CDC* pDC, int x1, int y1, int ugaoOkoCentraRotacije);
	void DrawSaksija(CDC* pDC);
	void DrawText(CDC* pDC, int size, char* text, int x, int y, int degrees, COLORREF color);

// Implementation
public:
	virtual ~CkaktusView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in kaktusView.cpp
inline CkaktusDoc* CkaktusView::GetDocument() const
   { return reinterpret_cast<CkaktusDoc*>(m_pDocument); }
#endif

