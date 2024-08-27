#pragma once
#pragma comment(lib, "Winmm.lib")

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>

// COLOR CODE
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

// MOVEMENT
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13
#define KEY_SPACE 32

// SOUNDTRACK
#define MOVE_SOUND 0
#define WIN_SOUND 1
#define LOSE_SOUND 2
#define MENU_SOUND 4
#define ERROR_SOUND 5
#define CHOOSE_SOUND 6

using namespace std;

struct Console {
	static HWND consoleWindow;    								//Handle huong toi cua so console
	static HANDLE consoleOutput;  								//Handle huong toi output console
	static HMENU systemMenu; 	  								//Handle huong toi menu da bi thay doi

	static void setupConsole();									//Cai dat man hinh console

	static void disableCtrButton(bool, bool, bool);				//Vo hieu hoa nut phong to, thu nho, close
	static void hideScrollbar();								//An hien thanh cuon
	static void showCursor(bool); 								//An hien con tro
	static void disableMouseInput(); 							//Vo hieu hoa chuot
	static void disableSelection();								//Vo hieu hoa boi den chu
	static void disableResizeWindow();							//Vo hieu hoa thay doi kich thu man hinh
	static void setAndCenterWindow();
	static void setConsoleTitle();

	static void setColor(int, int);								//Thiet lap mau
	static void gotoXY(int, int);								//Di chuyen con tro den toa do x, y 

	static void clearConsole(); 								//Xoa man hinh console
	static void playSound(int);  								//Choi nhac
};