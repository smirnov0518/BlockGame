#pragma once
#include <Windows.h>

class SameGameBoard
{
private:
	int height=35;
	int width=35;
	static const int rows=15;
	static const int colums=15;
	int fieldsRemain=0;

	int board[rows][colums];

	COLORREF colors[4]={RGB(0, 0, 0),RGB(255, 0, 0),RGB(255, 255, 64),RGB(0, 0, 255 )};

	enum Direction   // for  deleteNeighborBlocks function
	{
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};

	int deleteNeighborBlocks(int row, int col, int color, Direction direction);
	void rebuildBoard();
public:
	SameGameBoard()=default;
	COLORREF getBoardSpace(int row, int col){
		if (row >= 0 && row < rows && col >= 0 && col < colums)return colors[board[row][col]];
		return colors[0];
	}
	int getHeight()const { return height; }
	int getWidth()const { return width; }
	int getRows()const { return rows; }
	int getColums()const { return colums; }
	int getRemain()const { return fieldsRemain; }

	int deleteBlocks(int row,int col);	// returns how many blocks was deleted
	bool isGameOver()const;	// checks possible moves
	int getRemainingCount()const { return fieldsRemain; }

	void setupBoard();
};

