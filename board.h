#pragma once
#ifndef BOARDH
#define BOARDH

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include "stdafx.h"

using namespace std;

class Board{
	private:
		int maze[16][32];
		int x, y; //starting coodinates of the player
	public:
		Board();
		int get_x();
		int get_y();
		void change_x(int);
		void change_y(int);
		void displayMaze();
		void generatePath(int, int , int, int);
		void randomizeOpenSpaces();
		void setPerson();
		int movePerson();
};

#endif

