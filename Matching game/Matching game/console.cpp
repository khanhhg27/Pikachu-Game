#include "console.h"

HWND Console::consoleWindow = GetConsoleWindow();
HANDLE Console::consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
HMENU Console::systemMenu = GetSystemMenu(consoleWindow, false);

void Console::setupConsole() {
	system("color 70");
	setConsoleTitle();
	setAndCenterWindow();
	disableMouseInput(); 							//Vo hieu hoa chuot
	disableSelection();								//Vo hieu hoa boi den chu
	disableResizeWindow();							//Vo hieu hoa thay doi kich thuoc man hinh
	disableCtrButton(true, false, false);			//Vo hieu hoa nut phong to, thu nho, close
	hideScrollbar();								//An thanh cuon
	showCursor(false); 								//An hien con tro
}

void Console::disableResizeWindow() {
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_SIZEBOX);
}

void Console::disableCtrButton(bool Max, bool Min, bool Close) {
	if (Close == 1) {
		DeleteMenu(systemMenu, SC_CLOSE, MF_BYCOMMAND);
	}
	if (Min == 1) {
		DeleteMenu(systemMenu, SC_MINIMIZE, MF_BYCOMMAND);
	}
	if (Max == 1) {
		DeleteMenu(systemMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	}
}

void Console::hideScrollbar() {
	ShowScrollBar(consoleWindow, SB_BOTH, 0);
}

void Console::showCursor(bool show) {
	CONSOLE_CURSOR_INFO info = { 1,show };
	SetConsoleCursorInfo(consoleOutput, &info);
}

void Console::disableMouseInput() {
	DWORD prev_mode;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

void Console::disableSelection() {
	SetConsoleMode(consoleWindow, ~ENABLE_QUICK_EDIT_MODE);
}

void Console::setAndCenterWindow() {
	RECT rectClient, rectWindow;
	GetClientRect(consoleWindow, &rectClient), GetWindowRect(consoleWindow, &rectWindow);
	int width = 1200;
	int height = 600;
	int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
		posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	MoveWindow(consoleWindow, posX, posY, width, height, TRUE);
}

void Console::clearConsole() {
	system("cls");
}

void Console::setColor(int background, int text) {
	SetConsoleTextAttribute(consoleOutput, background * 16 + text);
}

void Console::gotoXY(int posX, int posY) {
	COORD Position;
	Position.X = posX;
	Position.Y = posY;
	SetConsoleCursorPosition(consoleOutput, Position);
}

void Console::setConsoleTitle() {
	SetConsoleTitle(TEXT("PIKACHU ONET ANIMAL MATCHING GAME.exe"));
}

void Console::playSound(int i) {
	static vector<const wchar_t*> soundFile{ L"Move.wav", L"Win.wav", L"Lose.wav", L"Menu.wav", L"Error.wav", L"Choose.wav" };
	PlaySound(soundFile[i], NULL, SND_FILENAME | SND_ASYNC);
}