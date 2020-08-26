
// SecondSameView.h : interface of the CSecondSameView class
//

#pragma once


class CSecondSameView : public CView
{
protected: // create from serialization only
	CSecondSameView() noexcept;
	DECLARE_DYNCREATE(CSecondSameView)

// Attributes
public:
	CSecondSameDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CSecondSameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	void resizeWindow();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in SecondSameView.cpp
inline CSecondSameDoc* CSecondSameView::GetDocument() const
   { return reinterpret_cast<CSecondSameDoc*>(m_pDocument); }
#endif

