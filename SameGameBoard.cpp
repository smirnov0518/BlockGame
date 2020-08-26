#include "pch.h"
#include <iostream>
#include "SameGameBoard.h"


int SameGameBoard::deleteNeighborBlocks(int row, int col, int color, Direction direction)	// recursive function for deleting one color blocks
{
	if (row<0 || row >= rows || col < 0 || col >= colums)return 0;
	if (board[row][col] != color)return 0;
	board[row][col] = 0;
	int count = 1;
	if (direction != DIRECTION_DOWN) {	// we can not move where we came from
		count += deleteNeighborBlocks(row + 1, col, color, DIRECTION_UP);
	}
	if (direction != DIRECTION_UP) {
		count += deleteNeighborBlocks(row - 1, col, color, DIRECTION_DOWN);
	}
	if (direction != DIRECTION_LEFT) {
		count += deleteNeighborBlocks(row, col - 1, color, DIRECTION_RIGHT);
	}
	if (direction != DIRECTION_RIGHT) {
		count += deleteNeighborBlocks(row, col + 1, color, DIRECTION_LEFT);
	}
	return count;
}

void SameGameBoard::rebuildBoard()	// after deleting
{
	/////////////////////////// move blocks down

	for (size_t i = 0; i < colums; i++){
		int firstEmptyField = rows - 1;
		int firstEngagedField = rows - 1;
		while (firstEmptyField >= 0) {
			if (board[firstEmptyField][i] == 0) break;
			firstEmptyField--;
		}
		firstEngagedField = firstEmptyField - 1;
		while (firstEngagedField >= 0) {
			if (board[firstEngagedField][i] != 0) break;
			firstEngagedField--;
		}
		while (firstEngagedField >=0) {
			board[firstEmptyField][i] = board[firstEngagedField][i];
			if(board[firstEngagedField][i]!=0)firstEmptyField--;
			board[firstEngagedField][i] = 0;
			firstEngagedField--;
		}
	}
	/////////////////////// move colums left
	int nNextEmptyCol = 0;	
	int nNextOccupiedCol = nNextEmptyCol;
	while (nNextEmptyCol < colums && nNextOccupiedCol < colums)
	{
		
		while (nNextEmptyCol < colums &&
			board[rows - 1][nNextEmptyCol] != 0)
			nNextEmptyCol++;
		if (nNextEmptyCol < colums)
		{
			
			nNextOccupiedCol = nNextEmptyCol + 1;
			while (nNextOccupiedCol < colums &&
				board[rows - 1][nNextOccupiedCol] == 0)
				nNextOccupiedCol++;
			if (nNextOccupiedCol < colums)
			{
				for (int row = 0; row <rows; row++)
				{
					board[row][nNextEmptyCol] =
						board[row][nNextOccupiedCol];
					board[row][nNextOccupiedCol] = 0;
				}
			}
		}
	}
}

int SameGameBoard::deleteBlocks(int row, int col)
{
	if (row<0 || row >= rows || col < 0 || col >= colums)return -1;
	if (board[row][col] == 0)return -1;	
	int curBlock = board[row][col];		// receive block's color
	int count = -1;
	if (row - 1 >= 0 && board[row - 1][col] == curBlock ||	// look at neighbor blocks and compare their colors
		row + 1 < rows && board[row + 1][col] == curBlock ||
		col - 1 >= 0 && board[row][col - 1] == curBlock ||
		col + 1 < colums && board[row][col + 1] == curBlock) {
		count = 1;
		board[row][col] = 0;
		count += deleteNeighborBlocks(row - 1, col, curBlock, DIRECTION_DOWN);
		count += deleteNeighborBlocks(row + 1, col, curBlock, DIRECTION_UP);
		count += deleteNeighborBlocks(row, col - 1, curBlock, DIRECTION_RIGHT);
		count += deleteNeighborBlocks(row, col + 1, curBlock, DIRECTION_LEFT);

		rebuildBoard();
		fieldsRemain -= count;
	}
	return count;

}

bool SameGameBoard::isGameOver() const	// returns true if we haven't any possible moves
{
	
	for (int col = 0; col < colums; col++)	// it mean that no one block on the board has no blocks near it with the same color
	{
		for (int row = rows - 1; row >= 0; row--)
		{
			int color = board[row][col];
			if (color == 0)
				break;
			else
			{
				if (row - 1 >= 0 &&
					board[row - 1][col] == color)
					return false;
				else if (col + 1 < colums &&
					board[row][col + 1] == color)
					return false;
			}
		}
	}
	return true;
}


void SameGameBoard::setupBoard()
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < colums; j++)
		{
			board[i][j] = rand() % 3 + 1;	// randomize colors except the background color
		}
	}
	fieldsRemain = rows * colums;	
}

