#pragma once

#include <iostream>
#include <string>
#include "console.h"
#include <fstream>
#include <conio.h>
#include <ctime>
#include "login.h"

using namespace std;

struct Menu
{
	static int mainMenu(Account);									//Menu
	static int modeSelectMenu(Account);							//Menu play
	static void leaderBoard();								//Màn hình load file leaderboard
	static void helpScreen();								//Màn hình hướng dẫn
	static int exitScreen();								//Màn hình thoát
	static void printLogo();								//In ra logo
	static void printRectangle(int, int, int, int);			//In hình chữ nhật cạnh 1 nét
	static void printDoubleRectangle(int, int, int, int);	//In hình chữ nhật cạnh 2 nét
	static void printAnimation();							//In hiệu ứng mở đầu
	static void printPikachu();								//In pikachu
	static void drawFaceLeftPikachu();
	static void drawFaceRightPikachu();
	static void winScreen(Account);
	static int customScreen(Account);
	static void continueScreen();
};