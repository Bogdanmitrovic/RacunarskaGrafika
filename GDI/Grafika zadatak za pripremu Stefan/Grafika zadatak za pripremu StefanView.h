
// Grafika zadatak za pripremu StefanView.h : interface of the CGrafikazadatakzapripremuStefanView class
//

#pragma once


class CGrafikazadatakzapripremuStefanView : public CView
{
protected: // create from serialization only
	CGrafikazadatakzapripremuStefanView() noexcept;
	DECLARE_DYNCREATE(CGrafikazadatakzapripremuStefanView)

// Attributes
public:
	CGrafikazadatakzapripremuStefanDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DrawRegularPolygon(CDC* pDC, int cx, int cy, int n, int r, float rotAngle);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGrafikazadatakzapripremuStefanView();
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
};

#ifndef _DEBUG  // debug version in Grafika zadatak za pripremu StefanView.cpp
inline CGrafikazadatakzapripremuStefanDoc* CGrafikazadatakzapripremuStefanView::GetDocument() const
   { return reinterpret_cast<CGrafikazadatakzapripremuStefanDoc*>(m_pDocument); }
#endif

