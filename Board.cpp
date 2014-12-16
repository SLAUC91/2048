#include "Board.h"
#include <iostream>
#include <random>
using namespace std;

//Draw Info to Screen
void Board::Draw(){

	//Check if the Best score was set
	if (score > best){
		best = score;
	}

	system("cls");

	cout << "\t2048 Puzzle Game\n" << endl;
	cout << "\t--Metrics--" << endl;
	cout << "\tScore: " << score << "\tBest: " << best << "  " << "\tTurn: " << turn << endl;
	cout << "\n\n";

	for (int i = 0; i < SIZE; i++)
	{
		cout << "\t |";

		for (int j = 0; j < SIZE; j++)
		{
			if (Table[i][j].CheckSet())
				printf("%4d |", Table[i][j].GetValue());
			else
				printf("%4c |", ' a ');
		}

		cout << endl << endl;
	}

	cout << endl << "\tMoves: Arrow Keys, R - Reset, ESC - Exit" << endl;
}

//Reset Grid and counting elements
void Board::Reset(){
	score = 0;
	turn = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Table[i][j].UnSet();
			Table[i][j].SetValue(0);
		}
	}
	SetUpBoard();
}

//Generate a Random number with a proability of a 4, 10% of the time
int Board::Random(){
	//probability is 10% of a 4
	float prob = .1;

	std::random_device rd;
	std::uniform_int_distribution<int> distribution(1, 100);
	std::mt19937 engine(rd()); // Mersenne twister MT19937

	int value = distribution(engine);

	//10% chance for a random 4
	if (value < (int)(prob * 100))
	{
		value = 4;
	}
	else
	{
		value = 2;
	}

	return value;
}

//Add Random element somewhere on the grid
void Board::AddRandom(){
	int x, y;
	int length = 0;
	int index[SIZE*SIZE][2];

	for (x = 0; x < SIZE; x++) {
		for (y = 0; y < SIZE; y++) {
			if (Table[x][y].CheckSet() == 0) {
				index[length][0] = x;
				index[length][1] = y;
				length++;
			}
		}
	}

	//cout << length << endl;
	if (length > 0) {
		int r = rand() % length;
		x = index[r][0];
		y = index[r][1];
		Table[x][y].SetValue(Random());
		Table[x][y].Set();
	}
}

//Inintal setup of the board
void Board::SetUpBoard(){
	AddRandom();
	AddRandom();
	Draw();
	score = 0;
}

//Generic Matrix Tanspose Function
void Board::TransformMatrix(){
	int i, j, n = SIZE;
	Tile tmp;
	for (i = 0; i < n / 2; i++) {
		for (j = i; j < n - i - 1; j++) {
			tmp = Table[i][j];
			Table[i][j] = Table[j][n - i - 1];
			Table[j][n - i - 1] = Table[n - i - 1][n - j - 1];
			Table[n - i - 1][n - j - 1] = Table[n - j - 1][i];
			Table[n - j - 1][i] = tmp;
		}
	}
}

//Slides the Matrix in the upward direction 
void Board::MoveMatrix() {
	//Transverse the column
	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){

			//Check if tile is not Set
			if (!Table[j][i].CheckSet()){

				for (int k = j + 1; k < SIZE; k++){  //Find the Set tile

					if (Table[k][i].CheckSet()){

						//Move if tile is set to the empty tile
						Table[j][i] = Table[k][i];
						
						//Reset moved tiles
						Table[k][i].UnSet();
						Table[k][i].SetValue(0);

						break;
					}
				}
			}
		}
	}
}

//Merges Martix - Can be Optimized 
void Board::MergeMartix(){
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE-1; j++) //3
		{
			if (Table[j][i].GetValue() && Table[j][i].GetValue() == Table[j + 1][i].GetValue())
			{
				Table[j][i].SetValue(Table[j][i].GetValue() << 1);
				Table[j][i].Set();

				Table[j + 1][i].SetValue(0);
				Table[j + 1][i].UnSet();

				score += Table[j][i].GetValue();
			}
		}
}

//Move elements
inline void Board::InternalMoveUP(){
	MoveMatrix();
	MergeMartix();
	MoveMatrix();
}

inline void Board::InternalMoveDown(){
	TransformMatrix();
	TransformMatrix();
	InternalMoveUP();
	TransformMatrix();
	TransformMatrix();
}

inline void Board::InternalMoveLeft(){
	TransformMatrix();
	TransformMatrix();
	TransformMatrix();
	InternalMoveUP();
	TransformMatrix();
}

inline void Board::InternalMoveRight(){
	TransformMatrix();
	InternalMoveUP();
	TransformMatrix();
	TransformMatrix();
	TransformMatrix();
}

void Board::MoveUP(){
	CopyGrid();
	InternalMoveUP();
	if (CheckTable()){
		AddRandom();
		turn++;
		Draw();
	}
}

void Board::MoveDown(){
	CopyGrid();
	InternalMoveDown();
	if (CheckTable()){
		AddRandom();
		turn++;
		Draw();
	}
}

void Board::MoveLeft(){
	CopyGrid();
	InternalMoveLeft();
	if (CheckTable() == 1){
		AddRandom();
		turn++;
		Draw();
	}
}

void Board::MoveRight(){
	CopyGrid();
	InternalMoveRight();
	if (CheckTable() == 1){
		AddRandom();
		turn++;
		Draw();
	}
}

//Check if 2 tables have the same elements
bool Board::CheckTable()
{
	bool diff = false;

	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			if (BkTable[i][j].GetValue() != Table[i][j].GetValue()){
				diff = true;
				break;
			}
		}

	}
	return diff;
}

//Copy One grid to the other
void Board::CopyGrid(){
	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			BkTable[i][j] = Table[i][j];
		}
	}
}

Board::Board(){
	SetUpBoard();
};