
// SecondSameView.cpp : implementation of the CSecondSameView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SecondSame.h"
#endif

#include "SecondSameDoc.h"
#include "SecondSameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSecondSameView

IMPLEMENT_DYNCREATE(CSecondSameView, CView)

BEGIN_MESSAGE_MAP(CSecondSameView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CSecondSameView construction/destruction

CSecondSameView::CSecondSameView() noexcept
{
	// TODO: add construction code here

}

CSecondSameView::~CSecondSameView()
{
}

BOOL CSecondSameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSecondSameView drawing

void CSecondSameView::OnDraw(CDC* pDC)
{
	CSecondSameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// save device state (probably for protect)
	int nDCSave = pDC->SaveDC();

	CRect rcClient;
	GetClientRect(&rcClient);
	COLORREF clr = pDoc->getBoardSpace(-1, -1); // receive the background color

	pDC->FillSolidRect(&rcClient, clr);

	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	pDC->SelectObject(&br);

	for (int row = 0; row < pDoc->getRows(); row++)
	{
		for (int col = 0; col < pDoc->getColums(); col++)
		{
			clr = pDoc->getBoardSpace(row, col); // receive color of the field

			CRect rcBlock;	// current block
			rcBlock.top = row * pDoc->getHeight();
			rcBlock.left = col * pDoc->getWidth();
			rcBlock.right = rcBlock.left + pDoc->getWidth();
			rcBlock.bottom = rcBlock.top + pDoc->getHeight();

			// fill the block
			pDC->FillSolidRect(&rcBlock, clr);

			// paint the borded
			pDC->Rectangle(&rcBlock);
		}
	}

	pDC->RestoreDC(nDCSave);	// repair device 
	br.DeleteObject();	
	// TODO: add draw code for native data here
}


// CSecondSameView diagnostics

#ifdef _DEBUG
void CSecondSameView::AssertValid() const
{
	CView::AssertValid();
}

void CSecondSameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSecondSameDoc* CSecondSameView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSecondSameDoc)));
	return (CSecondSameDoc*)m_pDocument;
}
#endif //_DEBUG


// CSecondSameView message handlers


void CSecondSameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	resizeWindow();
	// TODO: Add your specialized code here and/or call the base class
}
void CSecondSameView::resizeWindow() {

	CSecondSameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);

	// we need to save client field at the same sizes, thats why we take a difference between window and client 
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();

	// new frame size based on gameboard's width and height 
	rcWindow.right = rcWindow.left + pDoc->getWidth() * pDoc->getColums() + nWidthDiff;
	rcWindow.bottom = rcWindow.top + pDoc->getHeight() * pDoc->getRows() + nHeightDiff;

	GetParentFrame()->MoveWindow(&rcWindow);
}

void CSecondSameView::OnLButtonDown(UINT nFlags, CPoint point)	
{
	CSecondSameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int x = point.x / pDoc->getWidth();
	int y = point.y / pDoc->getHeight();

	int count = pDoc->deleteBlocks(y, x);

	if (count > 0)
	{

		Invalidate();
		UpdateWindow();

		if (pDoc->isGameOver())
		{

			int remaining = pDoc->getRemainingCount();
			CString message;
			message.Format(_T("No more moves left\nBlocks remaining: %d"),
				remaining);

			MessageBox(message, _T("Game Over"), MB_OK | MB_ICONINFORMATION);
		}
	}
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDown(nFlags, point);
}
