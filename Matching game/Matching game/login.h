#pragma once

#include "console.h"
#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>
#include <fstream>

using namespace std;

struct Account {
	int Num = 0;			//To number each account, 0 = guest account
	string UserName;		
	string Password;
		
	//Information to store after finish the game
	bool isFinished = 0;
	int time = 0;
	int score = 0;
	int mode = 0; //0 = normal, 1 = hard, 2 = custom 3 x 4, 3 = custom 4 x 5, 4 = custom 5 x 6
};

struct LoginScreen {
	static void loginScreen(Account&);
	static bool doLogin(Account&);
	static void doSignup();
	static void printAccountName(Account);
};

void printLogo();
void printRectangle(int left, int top, int width, int height);
void printDoubleRectangle(int left, int top, int width, int height);