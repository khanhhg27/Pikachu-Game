#include "board.h"

Board::Board(int _top, int _left, int _height, int _width) {
	srand((unsigned int)time(NULL));

	top = _top;
	left = _left;
	height = _height;
	width = _width;

	pBoard = new Cell * [height];
	for (int i = 0; i < height; i++) {
		pBoard[i] = new Cell[width];
		for (int j = 0; j < width; j++) {
			pBoard[i][j].x_console = j + float(top) / 10; 
			pBoard[i][j].y_console = i + float(left) / 4;
			pBoard[i][j].x = i;
			pBoard[i][j].y = j;
		}
	}

	int loop = (width * height) / 2;
	while (loop) {
		int index, time = 2;
		char c = 'A' + rand() % 26;
		while (time) {
			index = rand() % (width * height);
			if (pBoard[index / width][index % width].pokemon == '0') {
				pBoard[index / width][index % width].pokemon = c;
				time--;
			}
		}
		loop--;
	}

	drawBoard(height, width, pBoard);
}

void Board::clearBoard(Cell** pBoard) {
	for (int i = 0; i < height; i++) {
		delete[] pBoard[i];
		pBoard[i] = NULL;
	}
	delete[] pBoard;
	pBoard = NULL;
}

char box[5][12] = {
			{" --------- "},
			{"|         |"},
			{"|         |"},
			{"|         |"},
			{" --------- "}
};

void Board::drawBoard(int height, int width, Cell** pBoard) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pBoard[i][j].drawCell(WHITE);
		}
	}
	Menu::printDoubleRectangle(top - 2, left - 1, width * 10 + 3, height * 4 + 2);
}

void Cell::drawCell(int color) {
	if (pokemon == '0')
		return;

	for (int i = 0; i < 5; i++) {
		Console::gotoXY(int(x_console * 10), int(y_console * 4) + i);
		cout << box[i];
	}

	Console::setColor(color, BLACK);

	for (int i = 1; i < 4; i++) {
		Console::gotoXY(int(x_console * 10) + 1, int(y_console * 4) + i);
		cout << "         ";
	}

	Console::gotoXY(int(x_console * 10) + 5, int(y_console * 4) + 2);
	cout << pokemon;

	Console::setColor(WHITE, BLACK);
}

void Cell::deleteCell() {
	Console::setColor(WHITE, BLACK);
	for (int i = 0; i < 5; i++) {
		Console::gotoXY(int(x_console * 10), int(y_console * 4) + i);
		cout << "           ";
	}
}

void Board::deleteBoard(int hieght, int width, Cell** pBoard) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pBoard[i][j].deleteCell();
		}
	}
}

void Board::shuffle(int height, int width, Cell** pBoard) {
	std::vector<char> pokeList;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (pBoard[i][j].pokemon != '0') {
				pokeList.push_back(pBoard[i][j].pokemon);
			}
		}
	}
	std::vector<char> pokeListAfterShuffle;
	int k = int(pokeList.size());
	for (int i = 0; i < k; i++) {
		int n = rand() % pokeList.size();
		pokeListAfterShuffle.push_back( pokeList[n] );
		pokeList.erase(pokeList.begin() + n);
	}
	for (int i = 0; i < height * width; i++) {
		if (pBoard[i / width][i % width].pokemon != '0') {
			pBoard[i / width][i % width].pokemon = pokeListAfterShuffle[0];
			pokeListAfterShuffle.erase(pokeListAfterShuffle.begin());
		}	
	}
	
	return;
}

void Board::getBackground(char**& background, int height, int width, int mode) {
	int heightConsole = height * 4 + 1;
	int widthConsole = width * 10 + 2;

	background = new char* [heightConsole];
	for (int i = 0; i < heightConsole; i++) {
		background[i] = new char[widthConsole];
	}

	if (mode == 0 || mode == 1) {	//standard mode
		ifstream ifs("BackGround\\background6x8.txt");

		string line;
		int count = 0;

		if (!ifs.is_open()) {
			exit(1);
		}

		while (!ifs.eof() && count < heightConsole) {
			getline(ifs, line);

			for (int i = 0; i < widthConsole; i++) {
				background[count][i] = line[i];
			}

			count++;
		}

		ifs.close();
	}
	else if (mode == 2) {	//custom mode 3x4
		ifstream ifs("BackGround\\background3x4.txt");

		string line;
		int count = 0;

		if (!ifs.is_open()) {
			exit(1);
		}

		while (!ifs.eof() && count < heightConsole) {
			getline(ifs, line);

			for (int i = 0; i < widthConsole; i++) {
				background[count][i] = line[i];
			}

			count++;
		}

		ifs.close();
	}
	else if (mode == 3) {	//custom mode 4x5
		ifstream ifs("BackGround\\background4x5.txt");

		string line;
		int count = 0;

		if (!ifs.is_open()) {
			exit(1);
		}

		while (!ifs.eof() && count < heightConsole) {
			getline(ifs, line);

			for (int i = 0; i < widthConsole; i++) {
				background[count][i] = line[i];
			}

			count++;
		}

		ifs.close();
	}
	else if (mode == 4) {	//custom mode 5x6
		ifstream ifs("BackGround\\background5x6.txt");

		string line;
		int count = 0;

		if (!ifs.is_open()) {
			exit(1);
		}

		while (!ifs.eof() && count < heightConsole) {
			getline(ifs, line);

			for (int i = 0; i < widthConsole; i++) {
				background[count][i] = line[i];
			}

			count++;
		}

		ifs.close();
	}
}

void Board::displayBackground(Cell** pBoard, char** background, int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (pBoard[i][j].pokemon == '0') {
				int x_ = int(pBoard[i][j].x_console * 10);
				int y_ = int(pBoard[i][j].y_console * 4);

				//Vẽ
				for (int h = pBoard[i][j].x * 4; h < pBoard[i][j].x * 4 + 5; h++) {
					for (int w = pBoard[i][j].y * 10; w < pBoard[i][j].y * 10 + 11; w++) {
						Console::gotoXY(x_ + w - pBoard[i][j].y * 10, y_ + h - pBoard[i][j].x * 4);
						std::cout << background[h][w];
					}
				}
			}
		}
	}
}

void Board::clearBackground(char** background, int height) {
	int heightConsole = 4 * height + 1;
	for (int i = 0; i < heightConsole; i++)
		delete[] background[i];
	delete[] background;
}

void Board::drawI(Cell cell_1, Cell cell_2) {
	Console::setColor(WHITE, RED);
	int x1 = int((cell_1.x_console * 10)) + 5;
	int y1 = int((cell_1.y_console * 4)) + 2;
	int x2 = int((cell_2.x_console * 10)) + 5;
	int y2 = int((cell_2.y_console * 4)) + 2;
	if (x1 == x2) {
		if (y1 < y2) {
			Console::gotoXY(x1, y1 + 1);
			putchar(30);
			for (int i = y1 + 2; i <= y2 - 2; i++) {
				Console::gotoXY(x1, i);
				putchar(179);
			}
			Console::gotoXY(x2, y2 - 1);
			putchar(31);
			return;
		}
		else {
			Console::gotoXY(x1, y1 - 1);
			putchar(31);
			for (int i = y1 - 2; i >= y2 + 2; i--) {
				Console::gotoXY(x1, i);
				putchar(179);
			}
			Console::gotoXY(x2, y2 + 1);
			putchar(30);
			return;
		}
	}
	//========================================================================//
	if (y1 == y2) {
		if (x1 < x2) {
			Console::gotoXY(x1 + 1, y1);
			putchar(17);
			for (int i = x1 + 2; i <= x2 - 2; i++) {
				Console::gotoXY(i, y1);
				putchar(45);
			}
			Console::gotoXY(x2 - 1, y2);
			putchar(16);
			return;
		}
		else {
			Console::gotoXY(x1 - 1, y1);
			putchar(16);
			for (int i = x1 - 2; i >= x2 + 2; i--) {
				Console::gotoXY(i, y1);
				putchar(45);
			}
			Console::gotoXY(x2 + 1, y2);
			putchar(17);
			return;
		}
	}
}

void Board::eraseI(Cell cell_1, Cell cell_2) {
	Console::setColor(WHITE, WHITE);
	int x1 = int((cell_1.x_console * 10)) + 5;
	int y1 = int((cell_1.y_console * 4)) + 2;
	int x2 = int((cell_2.x_console * 10)) + 5;
	int y2 = int((cell_2.y_console * 4)) + 2;
	if (x1 == x2) {
		if (y1 < y2) {
			Console::gotoXY(x1, y1 + 1);
			putchar(32);
			for (int i = y1 + 2; i <= y2 - 2; i++) {
				Console::gotoXY(x1, i);
				putchar(32);
			}
			Console::gotoXY(x2, y2 - 1);
			putchar(32);
			return;
		}
		else {
			Console::gotoXY(x1, y1 - 1);
			putchar(32);
			for (int i = y1 - 2; i >= y2 + 2; i--) {
				Console::gotoXY(x1, i);
				putchar(32);
			}
			Console::gotoXY(x2, y2 + 1);
			putchar(32);
			return;
		}
	}
	//========================================================================//
	if (y1 == y2) {
		if (x1 < x2) {
			Console::gotoXY(x1 + 1, y1);
			putchar(32);
			for (int i = x1 + 2; i <= x2 - 2; i++) {
				Console::gotoXY(i, y1);
				putchar(32);
			}
			Console::gotoXY(x2 - 1, y2);
			putchar(32);
			return;
		}
		else {
			Console::gotoXY(x1 - 1, y1);
			putchar(32);
			for (int i = x1 - 2; i >= x2 + 2; i--) {
				Console::gotoXY(i, y1);
				putchar(32);
			}
			Console::gotoXY(x2 + 1, y2);
			putchar(32);
			return;
		}
	}
}

void Board::drawL(Cell cell_1, Cell cell_C, Cell cell_2) {
	Console::setColor(WHITE, RED);
	int x1 = int((cell_1.x_console * 10)) + 5;
	int y1 = int((cell_1.y_console * 4)) + 2;
	int x2 = int((cell_2.x_console * 10)) + 5;
	int y2 = int((cell_2.y_console * 4)) + 2;
	int xC = int((cell_C.x_console * 10)) + 5;
	int yC = int((cell_C.y_console * 4)) + 2;
	// Down-right
	if (xC < x2 && yC > y1) {
		Console::gotoXY(x1, y1 + 1);
		putchar(30);
		for (int i = y1 + 2; i <= yC - 1; i++) {
			Console::gotoXY(x1, i);
			putchar(179);
		}
		for (int i = xC; i <= x2 - 2; i++) {
			Console::gotoXY(i, y2);
			putchar(45);
		}
		Console::gotoXY(x2 - 1, y2);
		putchar(16);
		return;
	}
	// Hoán vị cell_1 và cell_2
	if (xC < x1 && yC > y2) {
		Console::gotoXY(x1 - 1, y1);
		putchar(16);
		for (int i = x1 - 2; i >= xC; i--) {
			Console::gotoXY(i, y1);
			putchar(45);
		}
		for (int i = yC - 1; i >= y2 + 2; i--) {
			Console::gotoXY(x2, i);
			putchar(179);
		}
		Console::gotoXY(x2, y2 + 1);
		putchar(30);
		return;
	}
	//========================================================================//
	// Up-right
	if (xC < x2 && yC < y1) {
		Console::gotoXY(x1, y1 - 1);
		putchar(31);
		for (int i = y1 - 2; i >= yC + 1; i--) {
			Console::gotoXY(x1, i);
			putchar(179);
		}
		for (int i = xC; i <= x2 - 2; i++) {
			Console::gotoXY(i, y2);
			putchar(45);
		}
		Console::gotoXY(x2 - 1, y2);
		putchar(16);
		return;
	}
	// Hoán vị cell-1 và cell_2
	if (xC < x1 && yC < y2) {
		Console::gotoXY(x1 - 1, y1);
		putchar(16);
		for (int i = x1 - 2; i >= xC + 1; i--) {
			Console::gotoXY(i, y1);
			putchar(45);
		}
		for (int i = yC + 1; i <= y2 - 2; i++) {
			Console::gotoXY(x2, i);
			putchar(179);
		}
		Console::gotoXY(x2, y2 - 1);
		putchar(31);
		return;
	}
	//========================================================================//
	// Up-left
	if (yC < y2 && xC > x1) {
		Console::gotoXY(x1 + 1, y1);
		putchar(17);
		for (int i = x1 + 2; i <= xC; i++) {
			Console::gotoXY(i, y1);
			putchar(45);
		}
		for (int i = yC + 1; i <= y2 - 2; i++) {
			Console::gotoXY(x2, i);
			putchar(179);
		}
		Console::gotoXY(x2, y2 - 1);
		putchar(31);
		return;
	}
	//Hoán vị trí cell_1 và cell_2
	if (yC < y1 && xC > x2) {
		Console::gotoXY(x1, y1 - 1);
		putchar(31);
		for (int i = y1 - 2; i >= yC; i--) {
			Console::gotoXY(x1, i);
			putchar(179);
		}
		for (int i = xC; i >= x2 + 2; i--) {
			Console::gotoXY(i, y2);
			putchar(45);
		}
		Console::gotoXY(x2 + 1, y2);
		putchar(17);
		return;
	}
	//========================================================================//
	// Down-left
	if (yC > y2 && xC > x1) {
		Console::gotoXY(x1 + 1, y1);
		putchar(17);
		for (int i = x1 + 2; i <= xC; i++) {
			Console::gotoXY(i, y1);
			putchar(45);
		}
		for (int i = yC - 1; i >= y2 + 2; i--) {
			Console::gotoXY(x2, i);
			putchar(179);
		}
		Console::gotoXY(x2, y2 + 1);
		putchar(30);
		return;
	}
	//Hoán vị trí cell_1 và cell_2
	if (yC > y1 && xC > x2) {
		Console::gotoXY(x1, y1 + 1);
		putchar(30);
		for (int i = y1 + 2; i <= yC; i++) {
			Console::gotoXY(x1, i);
			putchar(179);
		}
		for (int i = xC - 1; i >= x2 + 2; i--) {
			Console::gotoXY(i, y2);
			putchar(45);
		}
		Console::gotoXY(x2 + 1, y2);
		putchar(17);
		return;
	}
}

void Board::eraseL(Cell cell_1, Cell cell_C, Cell cell_2) {
	Console::setColor(WHITE, WHITE);
	int x1 = int((cell_1.x_console * 10)) + 5;
	int y1 = int((cell_1.y_console * 4)) + 2;
	int x2 = int((cell_2.x_console * 10)) + 5;
	int y2 = int((cell_2.y_console * 4)) + 2;
	int xC = int((cell_C.x_console * 10)) + 5;
	int yC = int((cell_C.y_console * 4)) + 2;
	// Down-right
	if (xC < x2 && yC > y1) {
		Console::gotoXY(x1, y1 + 1);
		putchar(32);
		for (int i = y1 + 2; i <= yC - 1; i++) {
			Console::gotoXY(x1, i);
			putchar(32);
		}
		for (int i = xC; i <= x2 - 2; i++) {
			Console::gotoXY(i, y2);
			putchar(32);
		}
		Console::gotoXY(x2 - 1, y2);
		putchar(32);
		return;
	}
	// Hoán vị cell_1 và cell_2
	if (xC < x1 && yC > y2) {
		Console::gotoXY(x1 - 1, y1);
		putchar(32);
		for (int i = x1 - 2; i >= xC; i--) {
			Console::gotoXY(i, y1);
			putchar(32);
		}
		for (int i = yC - 1; i >= y2 + 2; i--) {
			Console::gotoXY(x2, i);
			putchar(32);
		}
		Console::gotoXY(x2, y2 + 1);
		putchar(32);
		return;
	}
	//========================================================================//
	// Up-right
	if (xC < x2 && yC < y1) {
		Console::gotoXY(x1, y1 - 1);
		putchar(32);
		for (int i = y1 - 2; i >= yC + 1; i--) {
			Console::gotoXY(x1, i);
			putchar(132);
		}
		for (int i = xC; i <= x2 - 2; i++) {
			Console::gotoXY(i, y2);
			putchar(32);
		}
		Console::gotoXY(x2 - 1, y2);
		putchar(32);
		return;
	}
	// Hoán vị cell-1 và cell_2
	if (xC < x1 && yC < y2) {
		Console::gotoXY(x1 - 1, y1);
		putchar(32);
		for (int i = x1 - 2; i >= xC + 1; i--) {
			Console::gotoXY(i, y1);
			putchar(32);
		}
		for (int i = yC + 1; i <= y2 - 2; i++) {
			Console::gotoXY(x2, i);
			putchar(32);
		}
		Console::gotoXY(x2, y2 - 1);
		putchar(32);
		return;
	}
	//========================================================================//
	// Up-left
	if (yC < y2 && xC > x1) {
		Console::gotoXY(x1 + 1, y1);
		putchar(32);
		for (int i = x1 + 2; i <= xC; i++) {
			Console::gotoXY(i, y1);
			putchar(32);
		}
		for (int i = yC + 1; i <= y2 - 2; i++) {
			Console::gotoXY(x2, i);
			putchar(32);
		}
		Console::gotoXY(x2, y2 - 1);
		putchar(32);
		return;
	}
	//Hoán vị trí cell_1 và cell_2
	if (yC < y1 && xC > x2) {
		Console::gotoXY(x1, y1 - 1);
		putchar(32);
		for (int i = y1 - 2; i >= yC; i--) {
			Console::gotoXY(x1, i);
			putchar(32);
		}
		for (int i = xC; i >= x2 + 2; i--) {
			Console::gotoXY(i, y2);
			putchar(32);
		}
		Console::gotoXY(x2 + 1, y2);
		putchar(32);
		return;
	}
	//========================================================================//
	// Down-left
	if (yC > y2 && xC > x1) {
		Console::gotoXY(x1 + 1, y1);
		putchar(32);
		for (int i = x1 + 2; i <= xC; i++) {
			Console::gotoXY(i, y1);
			putchar(32);
		}
		for (int i = yC - 1; i >= y2 + 2; i--) {
			Console::gotoXY(x2, i);
			putchar(32);
		}
		Console::gotoXY(x2, y2 + 1);
		putchar(32);
		return;
	}
	//Hoán vị trí cell_1 và cell_2
	if (yC > y1 && xC > x2) {
		Console::gotoXY(x1, y1 + 1);
		putchar(32);
		for (int i = y1 + 2; i <= yC; i++) {
			Console::gotoXY(x1, i);
			putchar(32);
		}
		for (int i = xC - 1; i >= x2 + 2; i--) {
			Console::gotoXY(i, y2);
			putchar(32);
		}
		Console::gotoXY(x2 + 1, y2);
		putchar(32);
		return;
	}
}

void Board::drawZ(Cell cell_1, Cell cell_C1, Cell cell_C2, Cell cell_2) {
	Console::setColor(WHITE, RED);
	int x1 = int((cell_1.x_console * 10)) + 5;
	int y1 = int((cell_1.y_console * 4)) + 2;
	int x2 = int((cell_2.x_console * 10)) + 5;
	int y2 = int((cell_2.y_console * 4)) + 2;
	int xC1 = int((cell_C1.x_console * 10)) + 5;
	int yC1 = int((cell_C1.y_console * 4)) + 2;
	int xC2 = int((cell_C2.x_console * 10)) + 5;
	int yC2 = int((cell_C2.y_console * 4)) + 2;
	// Vẽ Z cũng có 4 dạng 

   // Dạng 1: Right-Up-Right
	if (xC1 > x1 && yC1 > y2) {
		Console::gotoXY(x1 + 1, y1);
		putchar(17);
		for (int i = x1 + 2; i <= xC1; i++) {
			Console::gotoXY(i, y1);
			putchar(45);
		}
		for (int i = yC1 - 1; i >= yC2 + 1; i--) {
			Console::gotoXY(xC1, i);
			putchar(179);
		}
		for (int i = xC2; i <= x2 - 2; i++) {
			Console::gotoXY(i, yC2);
			putchar(45);
		}
		Console::gotoXY(x2 - 1, y2);
		putchar(16);
		return;
	}
	// Đi ngược lại
	if (xC1 < x1 && yC1 < y2) {
		Console::gotoXY(x1 - 1, y1);
		putchar(16);
		for (int i = x1 - 2; i >= xC1; i--) {
			Console::gotoXY(i, y1);
			putchar(45);
		}
		for (int i = yC1 + 1; i <= yC2; i++) {
			Console::gotoXY(xC1, i);
			putchar(179);
		}
		for (int i = xC2; i >= x2 + 2; i--) {
			Console::gotoXY(i, yC2);
			putchar(45);
		}
		Console::gotoXY(x2 + 1, y2);
		putchar(17);
		return;
	}
	// Dạng 2: Right-Down-Right
	if (xC1 > x1 && yC1 < y2) {
		Console::gotoXY(x1 + 1, y1);
		putchar(17);
		for (int i = x1 + 2; i <= xC1; i++) {
			Console::gotoXY(i, y1);
			putchar(45);
		}
		for (int i = yC1 + 1; i <= yC2 - 1; i++) {
			Console::gotoXY(xC1, i);
			putchar(179);
		}
		for (int i = xC2; i <= x2 - 2; i++) {
			Console::gotoXY(i, yC2);
			putchar(45);
		}
		Console::gotoXY(x2 - 1, y2);
		putchar(16);
		return;
	}
	// Đi ngược lại
	if (xC1 < x1 && yC1 > y2) {
		Console::gotoXY(x1 - 1, y1);
		putchar(16);
		for (int i = x1 - 2; i >= xC1; i--) {
			Console::gotoXY(i, y1);
			putchar(45);
		}
		for (int i = yC1 - 1; i >= yC2 + 1; i--) {
			Console::gotoXY(xC1, i);
			putchar(179);
		}
		for (int i = xC2; i >= x2 + 2; i--) {
			Console::gotoXY(i, yC2);
			putchar(45);
		}
		Console::gotoXY(x2 + 1, y2);
		putchar(17);
		return;
	}

	// Dạng 3: Down-right-down
	if (xC1 < x2 && yC1 > y1) {
		Console::gotoXY(x1, y1 + 1);
		putchar(30);
		for (int i = y1 + 2; i <= yC1 - 1; i++) {
			Console::gotoXY(x1, i);
			putchar(179);
		}
		for (int i = xC1; i <= xC2; i++) {
			Console::gotoXY(i, yC1);
			putchar(45);
		}
		for (int i = yC2 + 1; i <= y2 - 2; i++) {
			Console::gotoXY(x2, i);
			putchar(179);
		}
		Console::gotoXY(x2, y2 - 1);
		putchar(31);
		return;
	}
	// Đi ngược lại
	if (xC1 > x2 && yC1 < y1) {
		Console::gotoXY(x1, y1 - 1);
		putchar(31);
		for (int i = y1 - 2; i >= yC1 + 1; i--) {
			Console::gotoXY(x1, i);
			putchar(179);
		}
		for (int i = xC1; i >= xC2; i--) {
			Console::gotoXY(i, yC1);
			putchar(45);
		}
		for (int i = yC2; i >= y2 + 2; i--) {
			Console::gotoXY(x2, i);
			putchar(179);
		}
		Console::gotoXY(x2, y2 + 1);
		putchar(30);
		return;
	}

	// Dạng 4: Up-right-Up
	if (xC1 > x2 && yC1 > y1) {
		Console::gotoXY(x1, y1 + 1);
		putchar(30);
		for (int i = y1 + 2; i <= yC1 - 1; i++) {
			Console::gotoXY(x1, i);
			putchar(179);
		}
		for (int i = xC1; i >= xC2; i--) {
			Console::gotoXY(i, yC1);
			putchar(45);
		}
		for (int i = yC2 + 1; i <= y2 - 2; i++) {
			Console::gotoXY(x2, i);
			putchar(179);
		}
		Console::gotoXY(x2, y2 - 1);
		putchar(31);
		return;
	}
	//Đi ngược lại
	if (xC1 < x2 && yC1 < y1) {
		Console::gotoXY(x1, y1 - 1);
		putchar(31);
		for (int i = y1 - 2; i >= yC1 + 1; i--) {
			Console::gotoXY(x1, i);
			putchar(179);
		}
		for (int i = xC1; i <= xC2; i++) {
			Console::gotoXY(i, yC1);
			putchar(45);
		}
		for (int i = yC2 - 1; i >= y2 + 2; i--) {
			Console::gotoXY(x2, i);
			putchar(179);
		}
		Console::gotoXY(x2, y2 + 1);
		putchar(30);
		return;
	}
}

void Board::eraseZ(Cell cell_1, Cell cell_C1, Cell cell_C2, Cell cell_2) {
	Console::setColor(WHITE, WHITE);
	int x1 = int((cell_1.x_console * 10)) + 5;
	int y1 = int((cell_1.y_console * 4)) + 2;
	int x2 = int((cell_2.x_console * 10)) + 5;
	int y2 = int((cell_2.y_console * 4)) + 2;
	int xC1 = int((cell_C1.x_console * 10)) + 5;
	int yC1 = int((cell_C1.y_console * 4)) + 2;
	int xC2 = int((cell_C2.x_console * 10)) + 5;
	int yC2 = int((cell_C2.y_console * 4)) + 2;
	// Vẽ Z cũng có 4 dạng 

// Dạng 1: Right-Down-Right
	if (xC1 > x1 && yC1 > y2) {
		Console::gotoXY(x1 + 1, y1);
		putchar(32);
		for (int i = x1 + 2; i <= xC1; i++) {
			Console::gotoXY(i, y1);
			putchar(32);
		}
		for (int i = yC1 - 1; i >= yC2 + 1; i--) {
			Console::gotoXY(xC1, i);
			putchar(32);
		}
		for (int i = xC2; i <= x2 - 2; i++) {
			Console::gotoXY(i, yC2);
			putchar(32);
		}
		Console::gotoXY(x2 - 1, y2);
		putchar(32);
		return;
	}
	// Đi ngược lại
	if (xC1 < x1 && yC1 < y2) {
		Console::gotoXY(x1 - 1, y1);
		putchar(32);
		for (int i = x1 - 2; i >= xC1; i--) {
			Console::gotoXY(i, y1);
			putchar(32);
		}
		for (int i = yC1 + 1; i <= yC2 - 1; i++) {
			Console::gotoXY(xC1, i);
			putchar(32);
		}
		for (int i = xC2; i >= x2 - 2; i--) {
			Console::gotoXY(i, yC2);
			putchar(32);
		}
		Console::gotoXY(x2 - 1, y2);
		putchar(32);
		return;
	}
	// Dạng 2: Right-Up-Right
	if (xC1 > x1 && yC1 < y2) {
		Console::gotoXY(x1 + 1, y1);
		putchar(32);
		for (int i = x1 + 2; i <= xC1; i++) {
			Console::gotoXY(i, y1);
			putchar(32);
		}
		for (int i = yC1 + 1; i <= yC2 - 1; i++) {
			Console::gotoXY(xC1, i);
			putchar(32);
		}
		for (int i = xC2; i <= x2 - 2; i++) {
			Console::gotoXY(i, yC2);
			putchar(32);
		}
		Console::gotoXY(x2 - 1, y2);
		putchar(32);
		return;
	}
	// Đi ngược lại
	if (xC1 < x1 && yC1 > y2) {
		Console::gotoXY(x1 - 1, y1);
		putchar(32);
		for (int i = x1 - 2; i >= xC1; i--) {
			Console::gotoXY(i, y1);
			putchar(32);
		}
		for (int i = yC1 - 1; i >= yC2 + 1; i--) {
			Console::gotoXY(xC1, i);
			putchar(32);
		}
		for (int i = xC2; i >= x2 - 2; i--) {
			Console::gotoXY(i, yC2);
			putchar(32);
		}
		Console::gotoXY(x2 - 1, y2);
		putchar(32);
		return;
	}
	// Dạng 3: Up-right-up
	if (xC1 > x2 && yC1 > y1) {
		Console::gotoXY(x1, y1 + 1);
		putchar(32);
		for (int i = y1 + 2; i <= yC1 - 1; i++) {
			Console::gotoXY(x1, i);
			putchar(32);
		}
		for (int i = xC1; i >= xC2; i--) {
			Console::gotoXY(i, yC1);
			putchar(32);
		}
		for (int i = yC2 + 1; i <= y2 - 2; i++) {
			Console::gotoXY(xC2, i);
			putchar(32);
		}
		Console::gotoXY(x2, y2 - 1);
		putchar(32);
		return;
	}
	// Đi ngược lại
	if (xC1 > x2 && yC1 < y1) {
		Console::gotoXY(x1, y1 - 1);
		putchar(32);
		for (int i = y1 - 2; i >= yC1 + 1; i--) {
			Console::gotoXY(x1, i);
			putchar(32);
		}
		for (int i = xC1; i >= xC2 - 1; i--) {
			Console::gotoXY(i, yC1);
			putchar(32);
		}
		for (int i = yC2; i >= y2 - 2; i--) {
			Console::gotoXY(x2, i);
			putchar(32);
		}
		Console::gotoXY(x2, y2 - 1);
		putchar(32);
		return;
	}

	// Dạng 4: Down-right-down
	if (xC1 < x2 && yC1 > y1) {
		Console::gotoXY(x1, y1 + 1);
		putchar(32);
		for (int i = y1 + 2; i <= yC1 - 1; i++) {
			Console::gotoXY(x1, i);
			putchar(32);
		}
		for (int i = xC1; i <= xC2; i++) {
			Console::gotoXY(i, yC1);
			putchar(32);
		}
		for (int i = yC2 + 1; i <= y2 - 2; i++) {
			Console::gotoXY(xC2, i);
			putchar(32);
		}
		Console::gotoXY(x2, y2 - 1);
		putchar(32);
		return;
	}
	//Đi ngược lại
	if (xC1 < x2 && yC1 < y1) {
		Console::gotoXY(x1, y1 - 1);
		putchar(32);
		for (int i = y1 - 2; i >= yC1 + 1; i--) {
			Console::gotoXY(x1, i);
			putchar(32);
		}
		for (int i = xC1; i <= xC2; i++) {
			Console::gotoXY(i, yC1);
			putchar(32);
		}
		for (int i = yC2 - 1; i >= y2 - 2; i--) {
			Console::gotoXY(x2, i);
			putchar(32);
		}
		Console::gotoXY(x2, y2 - 1);
		putchar(32);
		return;
	}
}

void Board::drawU(Cell cell_1, Cell cell_C1, Cell cell_C2, Cell cell_2) {
	Console::setColor(WHITE, RED);
	int x1 = int((cell_1.x_console * 10)) + 5;
	int y1 = int((cell_1.y_console * 4)) + 2;
	int x2 = int((cell_2.x_console * 10)) + 5;
	int y2 = int((cell_2.y_console * 4)) + 2;
	int xC1 = int((cell_C1.x_console * 10)) + 5;
	int yC1 = int((cell_C1.y_console * 4)) + 2;
	int xC2 = int((cell_C2.x_console * 10)) + 5;
	int yC2 = int((cell_C2.y_console * 4)) + 2;

	if (xC1 < x1 && yC1 < y2) {
		for (int i = xC1; i <= x1 - 2; i++) {
			Console::gotoXY(i, y1);
			putchar(45);
		}
		Console::gotoXY(x1 - 1, y1);
		putchar(16);
		for (int i = yC1 + 1; i <= yC2 - 1; i++) {
			Console::gotoXY(xC1, i);
			putchar(179);
		}
		for (int i = xC2; i <= x2 - 2; i++) {
			Console::gotoXY(i, yC2);
			putchar(45);
		}
		Console::gotoXY(x2 - 1, y2);
		putchar(16);
		return;
	}

	if (xC1 < x1 && yC1 > y2) {
		for (int i = xC1; i <= x1 - 2; i++) {
			Console::gotoXY(i, y1);
			putchar(45);
		}
		Console::gotoXY(x1 - 1, y1);
		putchar(16);
		for (int i = yC1 - 1; i >= yC2 + 1; i--) {
			Console::gotoXY(xC1, i);
			putchar(179);
		}
		for (int i = xC2; i <= x2 - 2; i++) {
			Console::gotoXY(i, yC2);
			putchar(45);
		}
		Console::gotoXY(x2 - 1, y2);
		putchar(16);
		return;
	}

	//----------------------------------------------//
	if (xC1 > x1 && yC1 < y2) {
		for (int i = xC1; i >= x1 + 2; i--) {
			Console::gotoXY(i, y1);
			putchar(45);
		}
		Console::gotoXY(x1 + 1, y1);
		putchar(17);
		for (int i = yC1 + 1; i <= yC2 - 1; i++) {
			Console::gotoXY(xC1, i);
			putchar(179);
		}
		for (int i = xC2; i >= x2 + 2; i--) {
			Console::gotoXY(i, y2);
			putchar(45);
		}
		Console::gotoXY(x2 + 1, y2);
		putchar(17);
		return;
	}

	if (xC1 > x1 && yC1 > y2) {
		for (int i = xC1; i >= x1 + 2; i--) {
			Console::gotoXY(i, y1);
			putchar(45);
		}
		Console::gotoXY(x1 + 1, y1);
		putchar(17);
		for (int i = yC1 - 1; i >= yC2 + 1; i--) {
			Console::gotoXY(xC1, i);
			putchar(179);
		}
		for (int i = xC2; i >= x2 + 2; i--) {
			Console::gotoXY(i, y2);
			putchar(45);
		}
		Console::gotoXY(x2 + 1, y2);
		putchar(17);
		return;
	}
	//----------------------------------------------//
	if (yC1 < y1 && xC1 < x2) {
		for (int i = yC1 + 1; i <= y1 - 2; i++) {
			Console::gotoXY(x1, i);
			putchar(179);
		}
		Console::gotoXY(x1, y1 - 1);
		putchar(31);
		for (int i = xC1; i <= xC2; i++) {
			Console::gotoXY(i, yC1);
			putchar(45);
		}
		for (int i = yC2 + 1; i <= y2 - 2; i++) {
			Console::gotoXY(xC2, i);
			putchar(179);
		}
		Console::gotoXY(x2, y2 - 1);
		putchar(31);
		return;
	}

	if (yC1 < y1 && xC1 > x2) {
		for (int i = yC1 + 1; i <= y1 - 2; i++) {
			Console::gotoXY(x1, i);
			putchar(179);
		}
		Console::gotoXY(x1, y1 - 1);
		putchar(31);
		for (int i = xC1; i >= xC2; i--) {
			Console::gotoXY(i, yC1);
			putchar(45);
		}
		for (int i = yC2 + 1; i <= y2 - 2; i++) {
			Console::gotoXY(xC2, i);
			putchar(179);
		}
		Console::gotoXY(x2, y2 - 1);
		putchar(31);
		return;
	}
	//-------------------------------------------------//
	if (xC1 < x2 && yC1 > y1) {
		for (int i = yC1 - 1; i >= y1 + 2; i--) {
			Console::gotoXY(x1, i);
			putchar(179);
		}
		Console::gotoXY(x1, y1 + 1);
		putchar(30);
		for (int i = xC1; i <= xC2; i++) {
			Console::gotoXY(i, yC1);
			putchar(45);
		}
		for (int i = yC2 - 1; i >= y2 + 2; i--) {
			Console::gotoXY(xC2, i);
			putchar(179);
		}
		Console::gotoXY(x2, y2 + 1);
		putchar(30);
		return;
	}

	if (xC1 > x2 && yC1 > y1) {
		for (int i = yC1 - 1; i >= y1 + 2; i--) {
			Console::gotoXY(x1, i);
			putchar(179);
		}
		Console::gotoXY(x1, y1 + 1);
		putchar(30);
		for (int i = xC1; i >= xC2; i--) {
			Console::gotoXY(i, yC1);
			putchar(45);
		}
		for (int i = yC2 - 1; i >= y2 + 2; i--) {
			Console::gotoXY(xC2, i);
			putchar(179);
		}
		Console::gotoXY(x2, y2 + 1);
		putchar(30);
		return;
	}
}

void Board::eraseU(Cell cell_1, Cell cell_C1, Cell cell_C2, Cell cell_2) {
	Console::setColor(WHITE, WHITE);
	int x1 = int((cell_1.x_console * 10)) + 5;
	int y1 = int((cell_1.y_console * 4)) + 2;
	int x2 = int((cell_2.x_console * 10)) + 5;
	int y2 = int((cell_2.y_console * 4)) + 2;
	int xC1 = int((cell_C1.x_console * 10)) + 5;
	int yC1 = int((cell_C1.y_console * 4)) + 2;
	int xC2 = int((cell_C2.x_console * 10)) + 5;
	int yC2 = int((cell_C2.y_console * 4)) + 2;
	if (xC1 < x1 && yC1 < y2) {
		for (int i = xC1; i <= x1 - 2; i++) {
			Console::gotoXY(i, y1);
			putchar(32);
		}
		Console::gotoXY(x1 - 1, y1);
		putchar(32);
		for (int i = yC1 + 1; i <= yC2 - 1; i++) {
			Console::gotoXY(xC1, i);
			putchar(32);
		}
		for (int i = xC2; i <= x2 - 2; i++) {
			Console::gotoXY(i, yC2);
			putchar(32);
		}
		Console::gotoXY(x2 - 1, y2);
		putchar(32);
		return;
	}

	if (xC1 < x1 && yC1 > y2) {
		for (int i = xC1; i <= x1 - 2; i++) {
			Console::gotoXY(i, y1);
			putchar(32);
		}
		Console::gotoXY(x1 - 1, y1);
		putchar(16);
		for (int i = yC1 - 1; i >= yC2 + 1; i--) {
			Console::gotoXY(xC1, i);
			putchar(32);
		}
		for (int i = xC2; i <= x2 - 2; i++) {
			Console::gotoXY(i, yC2);
			putchar(32);
		}
		Console::gotoXY(x2 - 1, y2);
		putchar(32);
		return;
	}
	//----------------------------------------------//
	if (xC1 > x1 && yC1 < y2) {
		for (int i = xC1; i >= x1 + 2; i--) {
			Console::gotoXY(i, y1);
			putchar(32);
		}
		Console::gotoXY(x1 + 1, y1);
		putchar(32);
		for (int i = yC1 + 1; i <= yC2 - 1; i++) {
			Console::gotoXY(xC1, i);
			putchar(32);
		}
		for (int i = xC2; i >= x2 + 2; i--) {
			Console::gotoXY(i, y2);
			putchar(32);
		}
		Console::gotoXY(x2 + 1, y2);
		putchar(32);
		return;
	}


	if (xC1 > x1 && yC1 > y2) {
		for (int i = xC1; i >= x1 + 2; i--) {
			Console::gotoXY(i, y1);
			putchar(32);
		}
		Console::gotoXY(x1 + 1, y1);
		putchar(32);
		for (int i = yC1 - 1; i >= yC2 + 1; i--) {
			Console::gotoXY(xC1, i);
			putchar(32);
		}
		for (int i = xC2; i >= x2 + 2; i--) {
			Console::gotoXY(i, y2);
			putchar(32);
		}
		Console::gotoXY(x2 + 1, y2);
		putchar(32);
		return;
	}
	//----------------------------------------------//
	if (yC1 < y1 && xC1 < x2) {
		for (int i = yC1 + 1; i <= y1 - 2; i++) {
			Console::gotoXY(x1, i);
			putchar(32);
		}
		Console::gotoXY(x1, y1 - 1);
		putchar(32);
		for (int i = xC1; i <= xC2; i++) {
			Console::gotoXY(i, yC1);
			putchar(32);
		}
		for (int i = yC2 + 1; i <= y2 - 2; i++) {
			Console::gotoXY(xC2, i);
			putchar(32);
		}
		Console::gotoXY(x2, y2 - 1);
		putchar(32);
		return;
	}


	if (yC1 < y1 && xC1 > x2) {
		for (int i = yC1 + 1; i <= y1 - 2; i++) {
			Console::gotoXY(x1, i);
			putchar(32);
		}
		Console::gotoXY(x1, y1 - 1);
		putchar(32);
		for (int i = xC1; i >= xC2; i--) {
			Console::gotoXY(i, yC1);
			putchar(32);
		}
		for (int i = yC2 + 1; i <= y2 - 2; i++) {
			Console::gotoXY(xC2, i);
			putchar(32);
		}
		Console::gotoXY(x2, y2 - 1);
		putchar(32);
		return;
	}
	//-------------------------------------------------//
	if (xC1 < x2 && yC1 > y1) {
		for (int i = yC1 - 1; i >= y1 + 2; i--) {
			Console::gotoXY(x1, i);
			putchar(32);
		}
		Console::gotoXY(x1, y1 + 1);
		putchar(32);
		for (int i = xC1; i <= xC2; i++) {
			Console::gotoXY(i, yC1);
			putchar(32);
		}
		for (int i = yC2 - 1; i >= y2 + 2; i--) {
			Console::gotoXY(xC2, i);
			putchar(32);
		}
		Console::gotoXY(x2, y2 + 1);
		putchar(32);
		return;
	}

	if (xC1 > x2 && yC1 > y1) {
		for (int i = yC1 - 1; i >= y1 + 2; i--) {
			Console::gotoXY(x1, i);
			putchar(32);
		}
		Console::gotoXY(x1, y1 + 1);
		putchar(30);
		for (int i = xC1; i >= xC2; i--) {
			Console::gotoXY(i, yC1);
			putchar(32);
		}
		for (int i = yC2 - 1; i >= y2 + 2; i--) {
			Console::gotoXY(xC2, i);
			putchar(32);
		}
		Console::gotoXY(x2, y2 + 1);
		putchar(32);
		return;
	}
}