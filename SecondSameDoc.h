
// SecondSameDoc.h : interface of the CSecondSameDoc class
//

#pragma once
#include "SameGameBoard.h"

class CSecondSameDoc : public CDocument
{
protected: // create from serialization only
	CSecondSameDoc() noexcept;
	DECLARE_DYNCREATE(CSecondSameDoc)

// Attributes
public:

// Operations
public:

	int getHeight()const { return board.getHeight(); }
	int getWidth()const { return board.getWidth(); }
	int getRows()const { return board.getRows(); }
	int getColums()const { return board.getColums(); }
	int getRemain()const { return board.getRemain(); }
	COLORREF getBoardSpace(int row, int col) { return board.getBoardSpace(row,col); }

	int deleteBlocks(int row, int col){ return board.deleteBlocks(row, col); }
	bool isGameOver()const { return board.isGameOver(); }
	int getRemainingCount()const { return board.getRemainingCount(); }
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CSecondSameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	SameGameBoard board;
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
