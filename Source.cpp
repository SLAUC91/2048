#include "Board.h"
#include <Windows.h>

void Run() {
	Board * Entity = new Board();

	for (;;){
		//arrow up
		if (GetAsyncKeyState(VK_UP))
		{
			Entity->MoveUP();
		}
		//arrow down
		else if (GetAsyncKeyState(VK_DOWN))
		{
			Entity->MoveDown();
		}
		//arrow left
		else if (GetAsyncKeyState(VK_LEFT))
		{
			Entity->MoveLeft();
		}
		//arrow right
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			Entity->MoveRight();
		}
		//r
		else if (GetAsyncKeyState('R'))
		{
			Entity->Reset();
		}
		//esc 
		else if (GetAsyncKeyState(VK_ESCAPE)){
			break;
		}

		Sleep(150);
	}

	delete Entity;
}

int main(){

	Run();

	return 0;
}