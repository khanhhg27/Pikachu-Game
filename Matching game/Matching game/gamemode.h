#pragma once

#include "console.h"
#include "board.h"
#include "gameplay.h"
#include "linkedlistutility.h"
#include "login.h"
#include <cmath>
#include <ctime>

//For normal mode
#define TOP 28	//Vị trí của board trên console thụt vào 28 dấu spaces và 8 dấu xuống hàng
#define LEFT 8
#define HEIGHT 6
#define WIDTH 8

//For hard mode
#define H_TOP 28
#define H_LEFT 8
#define H_HEIGHT 6
#define H_WIDTH 8

struct GameMode {
	static void createNormalGame(Account&);
	static void createHardGame_2DPointerArray(Account&);
	static void createHardGame_LinkedList(Account&);
	static void createCustomGame(Account&, int height, int width, int mode);
};

void moveSuggestion(int, int, Cell**);