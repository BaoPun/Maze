#include "stdafx.h"
#include "board.h"


Board::Board(){
	//initialize coordinates of the player
	x = y = 0;

	//initialize the maze here
	//walls = 0, open path = 1

	//start by initializing the starting and end points of the maze
	int start_x = rand() % 14 + 1, start_y = 0; 
	int end_x = rand() % 14 + 1, end_y = 31;

	//now we figured where on the left the player will start
	x = start_x;
	y = 0;

	//walls first
	//top and bottom edge
	for (int i = 0; i < 32; i++) {
		maze[0][i] = 0;
		maze[15][i] = 0;
	}
	//left and right edge, all walls except for starting player position and ending position
	for (int i = 1; i < 15; i++) {
		maze[i][0] = (i == start_x) ? 1 : 0;
		maze[i][31] = (i == end_x) ? 1 : 0;
	}

	//initialize middle of board to 0 at first
	for (int i = 1; i < 15; i++) {
		for (int j = 1; j < 31; j++)
			maze[i][j] = 0;
	}

	//whereever we started, must allocate at least 1 open pathway for me and the end
	maze[start_x][1] = 1;
	maze[end_x][30] = 1;

	generatePath(start_x, 1, end_x, 30);
	randomizeOpenSpaces();
	
}

int Board::get_x() {
	return x;
}

int Board::get_y() {
	return y;
}

//recursion: generate the solution 
//a and b are where we are at right now, x and y are the final destination of the maze
void Board::generatePath(int a, int b, int x, int y) {
	if (a == x && b == y)
		return;
	//choose to either go up, right, or down (0, 1, 2, respectively)
	int randPath = rand() % 3; //0-2
	if (randPath == 0) { //up
		if (a == 1) { //if we try to go up, but run into a wall.  go right instead
			if (b == y) { //if we can't go right, however, then just move down
				maze[a + 1][b] = 1;
				generatePath(a + 1, b, x, y);
			}
			else {
				maze[a][b + 1] = 1;
				generatePath(a, b + 1, x, y);
			}
		}
		else { //go up
			maze[a - 1][b] = 1;
			generatePath(a - 1, b, x, y);
		}
	}
	else if (randPath == 1) { //right
		if (b == y) { //we bumped into wall
			//determine which direction is closer to exit
			if (a - x > 0) { //positive, move up
				maze[a - 1][b] = 1;
				generatePath(a - 1, b, x, y);
			}
			else { //negative, move down
				maze[a + 1][b] = 1;
				generatePath(a + 1, b, x, y);
			}
		}
		else { //we're not in wall, move right
			maze[a][b + 1] = 1;
			generatePath(a, b + 1, x, y);
		}
	}
	else { //down
		if (a == 14) { //if we try to go down, but run into a wall.  go right instead
			if (b == y) { //unable to move right because we're stuck in wall, go up instead
				maze[a - 1][b] = 1;
				generatePath(a - 1, b, x, y);
			}
			else {
				maze[a][b + 1] = 1;
				generatePath(a, b + 1, x, y);
			}
		}
		else {
			maze[a + 1][b] = 1;
			generatePath(a + 1, b, x, y);
		}
	}
}

void Board::randomizeOpenSpaces() {
	for (int i = 1; i < 15; i++) {
		for (int j = 1; j < 31; j++) {
			int space = rand() % 2; //0-1
			if (maze[i][j] != 1)
				maze[i][j] = space;
		}
	}
}

void Board::change_x(int i) {
	x = i;
}

void Board::change_y(int j) {
	y = j;
}

void Board::displayMaze() {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 32; j++) {
			if (maze[i][j] == 0)
				cout << "$";
			else if (maze[i][j] == 1)
				cout << "-";
			else if (maze[i][j] == 2) {
				if (i == x && j == y)
					cout << "?";
				else
					cout << "-";
			}
		}
		cout << endl;
	}
}

void Board::setPerson() {
	//In console, the path reads Y and then X, so simply inverting coordinates.
	COORD coordinate;
	coordinate.X = y; 
	coordinate.Y = x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

int Board::movePerson() {
	char input;
	int a, b;
	int moveCount = 0;
	while (1) {
		system("CLS");
		displayMaze();
		cout << "Move counter: " << moveCount << "\n";
		setPerson();
		cout << "P"; //cursor on player displayed with a "P"
		
		input = _getch();
		a = x;
		b = y;

		if (input == 'w') {
			x--;
			if (maze[x][y] == 0)
				x++;
			else
				moveCount++;
		}
		else if (input == 's') {
			x++;
			if (maze[x][y] == 0)
				x--;
			else
				moveCount++;
		}
		else if (input == 'a') {
			y--;
			if (maze[x][y] == 0)
				y++;
			else
				moveCount++;
		}
		else if (input == 'd') {
			y++;
			if (maze[x][y] == 0)
				y--;
			else
				moveCount++;
		}
		if (y == 31) {
			system("CLS");
			return moveCount;
		}
	}
}