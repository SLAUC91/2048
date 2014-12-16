#ifndef _Board_H_
#define _Board_H_

#include "Tile.h"
#include <Windows.h>

#define SIZE 4

class Board{
private:
	int score = 0;
	int turn = 0; 
	int best = 0;

	Tile Table[SIZE][SIZE];
	Tile BkTable[SIZE][SIZE];

	int Random();
	bool CheckTable();

	inline void InternalMoveUP();
	inline void InternalMoveDown();
	inline void InternalMoveLeft();
	inline void InternalMoveRight();

	void AddRandom();
	void SetUpBoard();

	void TransformMatrix();
	void MoveMatrix();
	void MergeMartix();
	void CopyGrid();
	void Draw();

public:
	void MoveUP();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Reset();

	Board();
};

#endif