// Maze.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "./board.h"

int main(){
	srand((unsigned int)time(NULL));

	Board maze;
	int numMoves = maze.movePerson();
	cout << "You have made " << numMoves << " moves to get out of this maze, congratulations!\n";
	system("pause");
    return 0;
}

