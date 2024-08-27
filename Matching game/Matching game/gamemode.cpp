#include "gamemode.h"

void GameMode::createNormalGame(Account& account) {
	clock_t start, end;
	double playTime = 0;
	start = clock();

	Board board(TOP, LEFT, HEIGHT, WIDTH);
	GamePlay gameplay;
	gameplay.score = 0;
	pair<int, int> check(-2, -2);

	pair<int, int> selectedCell[2] = { { -2, -2}, {-2, -2} };
	int remainCell = 2;	// remaining Selectable Cells
	pair<int, int> curPos(0, 0);
	int isPlaying = 1; // 1 = đang chơi, 0 là hết game

	int key = 0;
	int EXIT = 0;

	char** background;
	Board::getBackground(background, HEIGHT, WIDTH, 0);

	while (isPlaying) {
		board.drawBoard(HEIGHT, WIDTH, board.pBoard);				//Vẽ board hiện tại
		LoginScreen::printAccountName(account);

		if (gameplay.score < 0)
			gameplay.score = 0;
		gameplay.remainingCell = 0;
		gameplay.validPair = 0;

		//Count remainingCells
		for (int i = 0; i < HEIGHT; i++)
			for (int j = 0; j < WIDTH; j++)
				if (board.pBoard[i][j].pokemon != '0')
					gameplay.remainingCell += 1;


		//Count validPairs
		for (int i = 0; i < HEIGHT * WIDTH; i++) {
			if (board.pBoard[i / WIDTH][i % WIDTH].pokemon != '0')
				for (int j = i + 1; j < HEIGHT * WIDTH; j++) {
					if (board.pBoard[j / WIDTH][j % WIDTH].pokemon == board.pBoard[i / WIDTH][i % WIDTH].pokemon) {
						check = gameplay.check2Cells(board.pBoard, HEIGHT, WIDTH, board.pBoard[j / WIDTH][j % WIDTH], board.pBoard[i / WIDTH][i % WIDTH]);
					
						if (check.first != -2 || check.second != -2)
							gameplay.validPair += 1;
					
						check = make_pair(-2, -2);
					}
				}
		}

		//display some infos
		Console::gotoXY(65, 0);
		std::cout << "MODE: NORMAL";
		if (gameplay.score >= 10) {
			Console::gotoXY(85, 0);
			std::cout << "SCORE: " << gameplay.score;
		}
		else {
			Console::gotoXY(85, 0);
			std::cout << "SCORE: 0" << gameplay.score;
		}
		if (gameplay.remainingCell >= 10) {
			Console::gotoXY(100, 0);
			std::cout << "RemainingCell(s): " << gameplay.remainingCell;
		}
		else {
			Console::gotoXY(100, 0);
			std::cout << "RemainingCell(s): 0" << gameplay.remainingCell;
		}

		if (gameplay.validPair >= 10) {
			Console::gotoXY(125, 0);
			std::cout << "ValidPair(s): " << gameplay.validPair;
		}
		else {
			Console::gotoXY(125, 0);
			std::cout << "ValidPair(s): 0" << gameplay.validPair;
		}
		
		Menu::printDoubleRectangle(114, 2, 29, 2);
		Console::gotoXY(115, 3);
		std::cout << "Press I for more information.";

		//Draw selected Cell
		for (int i = 0; i < HEIGHT * WIDTH; i++)
			if (board.pBoard[i / WIDTH][i % WIDTH].isSelected)
				board.pBoard[i / WIDTH][i % WIDTH].drawCell(YELLOW);

		//Draw cell pointed by cursor
		board.pBoard[curPos.first][curPos.second].drawCell(LIGHT_RED);

		//Lặp các phím
		if (gameplay.remainingCell != 0) {
			while (true) {					//Xài trong trường hợp người dùng không nhập vào 1 trong các phím ở dưới
				bool true_while_flag = 0;	//Cờ thoát vòng lặp while true
				bool isCurFound = 0;
				key = _getch();

				switch (key) {
				case KEY_ESC:
					end = clock();
					playTime += (double)(end - start) / CLOCKS_PER_SEC;

					Console::playSound(MENU_SOUND);
					std::system("cls");
					EXIT = Menu::exitScreen();
					if (EXIT == 0) {
						true_while_flag = 0;
						Board::displayBackground(board.pBoard, background, HEIGHT, WIDTH);

						start = clock();
						break;
					}
					else {
						Board::clearBackground(background, HEIGHT);
						board.clearBoard(board.pBoard);
						exit(0);
					}
				case KEY_RIGHT:
					Console::playSound(MOVE_SOUND);
					//Check về bên phải cùng hàng
					if (isCurFound == 0) {
						for (int j = curPos.second + 1; j < WIDTH; j++)
							if (board.pBoard[curPos.first][j].pokemon != '0') {
								isCurFound = 1;
								curPos.second = j;
								break;
							}
					}

					//Check theo đường xiên xuống 
					if (isCurFound == 0) {
						for (int i = curPos.first + 1; i < HEIGHT; i++) {
							for (int j = curPos.second + 1; j < WIDTH; j++) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//Check xiên lên
					if (isCurFound == 0) {
						for (int i = curPos.first - 1; i >= 0; i--) {
							for (int j = curPos.second + 1; j < WIDTH; j++) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//check ngược lại
					if (isCurFound == 0) {
						for (int j = 0; j < curPos.second; j++)
							if (board.pBoard[curPos.first][j].pokemon != '0') {
								isCurFound = 1;
								curPos.second = j;
								break;
							}
					}

					break;

				case KEY_LEFT:
					Console::playSound(MOVE_SOUND);
					//Check về bên trái cùng hàng
					if (isCurFound == 0) {
						for (int j = curPos.second - 1; j >= 0; j--)
							if (board.pBoard[curPos.first][j].pokemon != '0') {
								isCurFound = 1;
								curPos.second = j;
								break;
							}
					}

					//Check theo đường xiên xuống 
					if (isCurFound == 0) {
						for (int i = curPos.first + 1; i < HEIGHT; i++) {
							for (int j = curPos.second - 1; j >= 0; j--) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//Check xiên lên
					if (isCurFound == 0) {
						for (int i = curPos.first - 1; i >= 0; i--) {
							for (int j = curPos.second - 1; j >= 0; j--) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//check ngược lại
					if (isCurFound == 0) {
						for (int j = WIDTH - 1; j > curPos.second; j--)
							if (board.pBoard[curPos.first][j].pokemon != '0') {
								isCurFound = 1;
								curPos.second = j;
								break;
							}
					}
					break;

				case KEY_DOWN:
					Console::playSound(MOVE_SOUND);
					//Check thẳng xuống
					if (isCurFound == 0) {
						for (int i = curPos.first + 1; i < HEIGHT; i++)
							if (board.pBoard[i][curPos.second].pokemon != '0') {
								isCurFound = 1;
								curPos.first = i;
								break;
							}
					}

					//Check theo đường xiên xuống qua phải
					if (isCurFound == 0) {
						for (int j = curPos.second + 1; j < WIDTH; j++) {
							for (int i = curPos.first + 1; i < HEIGHT; i++) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//Check xiên xuống qua trái
					if (isCurFound == 0) {
						for (int j = curPos.second - 1; j >= 0; j--) {
							for (int i = curPos.first + 1; i < HEIGHT; i++) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//check ngược lại
					if (isCurFound == 0) {
						for (int i = 0; i < curPos.first; i++)
							if (board.pBoard[i][curPos.second].pokemon != '0') {
								isCurFound = 1;
								curPos.first = i;
								break;
							}
					}
					break;

				case KEY_UP:
					Console::playSound(MOVE_SOUND);
					//Check lên trên
					if (isCurFound == 0) {
						for (int i = curPos.first - 1; i >= 0; i--)
							if (board.pBoard[i][curPos.second].pokemon != '0') {
								isCurFound = 1;
								curPos.first = i;
								break;
							}
					}

					//Check theo đường xiên lên qua phải
					if (isCurFound == 0) {
						for (int j = curPos.second + 1; j < WIDTH; j++) {
							for (int i = curPos.first - 1; i >= 0; i--) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//Check xiên lên qua trái
					if (isCurFound == 0) {
						for (int j = curPos.second - 1; j >= 0; j--) {
							for (int i = curPos.first - 1; i > 0; i--) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//check ngược lại
					if (isCurFound == 0) {
						for (int i = HEIGHT - 1; i > curPos.first; i--)
							if (board.pBoard[i][curPos.second].pokemon != '0') {
								isCurFound = 1;
								curPos.first = i;
								break;
							}
					}
					break;

				case KEY_ENTER:
					//Nếu ô đã chọn hay chưa chọn
					if (board.pBoard[curPos.first][curPos.second].isSelected == 0)
						board.pBoard[curPos.first][curPos.second].isSelected = 1;
					else
						board.pBoard[curPos.first][curPos.second].isSelected = 0;

					//Nếu chọn
					if (board.pBoard[curPos.first][curPos.second].isSelected == 1) {
						remainCell--;
						board.pBoard[curPos.first][curPos.second].drawCell(YELLOW);

						if (remainCell == 1) {
							selectedCell[0].first = curPos.first;
							selectedCell[0].second = curPos.second;
						}
						else if (remainCell == 0) {
							selectedCell[1].first = curPos.first;
							selectedCell[1].second = curPos.second;
						}

						if (remainCell == 0) {
							Sleep(250);
							check = gameplay.check2Cells(board.pBoard, HEIGHT, WIDTH, board.pBoard[selectedCell[0].first][selectedCell[0].second], board.pBoard[selectedCell[1].first][selectedCell[1].second]);

							if (check.first != -2 || check.second != -2) { //check đúng
								gameplay.score += 2;
								Console::playSound(MOVE_SOUND);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].drawCell(GREEN);
								board.pBoard[selectedCell[1].first][selectedCell[1].second].drawCell(GREEN);
								gameplay.drawLine2Cells(board.pBoard, HEIGHT, WIDTH, TOP, LEFT, board.pBoard[selectedCell[0].first][selectedCell[0].second], board.pBoard[selectedCell[1].first][selectedCell[1].second]);
								Console::setColor(WHITE, BLACK);
								Sleep(500);

								gameplay.eraseLine2Cells(board.pBoard, HEIGHT, WIDTH, TOP, LEFT, board.pBoard[selectedCell[0].first][selectedCell[0].second], board.pBoard[selectedCell[1].first][selectedCell[1].second]);
								Console::setColor(WHITE, BLACK);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].deleteCell();
								board.pBoard[selectedCell[1].first][selectedCell[1].second].deleteCell();

								board.pBoard[selectedCell[0].first][selectedCell[0].second].pokemon = '0';
								board.pBoard[selectedCell[1].first][selectedCell[1].second].pokemon = '0';

								board.pBoard[selectedCell[0].first][selectedCell[0].second].isSelected = 0;
								board.pBoard[selectedCell[1].first][selectedCell[1].second].isSelected = 0;

								Board::displayBackground(board.pBoard, background, HEIGHT, WIDTH);

								remainCell = 2;
								selectedCell[0].first = -2;
								selectedCell[0].second = -2;
								selectedCell[1].first = -2;
								selectedCell[1].second = -2;
							}
							else {
								Console::playSound(ERROR_SOUND);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].drawCell(RED);
								board.pBoard[selectedCell[1].first][selectedCell[1].second].drawCell(RED);
								Sleep(500);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].drawCell(WHITE);
								board.pBoard[selectedCell[1].first][selectedCell[1].second].drawCell(WHITE);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].isSelected = 0;
								board.pBoard[selectedCell[1].first][selectedCell[1].second].isSelected = 0;

								remainCell = 2;
								selectedCell[0].first = -2;
								selectedCell[0].second = -2;
								selectedCell[1].first = -2;
								selectedCell[1].second = -2;
							}

							check = make_pair(-2, -2);
						}

					}

					//Nếu bỏ chọn
					else {
						remainCell++;

						board.pBoard[selectedCell[0].first][selectedCell[0].second].isSelected = 0;

						selectedCell[0].first = -2;
						selectedCell[0].second = -2;
					}
					break;
				case 'S':
					Console::playSound(MOVE_SOUND);
					gameplay.score -= 2;
					Console::gotoXY(70, 5);
					std::cout << "SHUFFLING...";
					Sleep(1000);
					Console::gotoXY(70, 5);
					std::cout << "            ";

					board.shuffle(HEIGHT, WIDTH, board.pBoard);
					break;
				case 's':
					Console::playSound(MOVE_SOUND);
					gameplay.score -= 2;
					Console::gotoXY(70, 5);
					std::cout << "SHUFFLING...";
					Sleep(1000);
					Console::gotoXY(70, 5);
					std::cout << "            ";

					board.shuffle(HEIGHT, WIDTH, board.pBoard);
					break;
				case 'A':
					Console::playSound(MOVE_SOUND);
					gameplay.score -= 2;
					moveSuggestion(HEIGHT, WIDTH, board.pBoard);
					Sleep(500);
					break;
				case 'a':
					Console::playSound(MOVE_SOUND);
					gameplay.score -= 2;
					moveSuggestion(HEIGHT, WIDTH, board.pBoard);
					Sleep(500);
					break;
				case 'I':
					end = clock();
					playTime += (double)(end - start) / CLOCKS_PER_SEC;

					Console::playSound(MENU_SOUND);
					Console::clearConsole();
					Console::setColor(WHITE, BLUE);
					Console::gotoXY(57, 0);
					std::cout << "Play time up to now: " << playTime << "s...";
					Console::setColor(WHITE, BLACK);

					Menu::helpScreen();

					Board::displayBackground(board.pBoard, background, HEIGHT, WIDTH);
					start = clock();
					break;
				case 'i':
					end = clock();
					playTime += (double)(end - start) / CLOCKS_PER_SEC;

					Console::playSound(MENU_SOUND);
					Console::clearConsole();
					Console::setColor(WHITE, BLUE);
					Console::gotoXY(57, 0);
					std::cout << "Play time up to now: " << playTime << "s...";
					Console::setColor(WHITE, BLACK);

					Menu::helpScreen();

					Board::displayBackground(board.pBoard, background, HEIGHT, WIDTH);
					start = clock();
					break;
				default:
					true_while_flag = 1;
					break;
				}
				if (true_while_flag == 0)
					break;
			}
		}
		else {
			Sleep(500);
		}

		if (gameplay.validPair == 0 && gameplay.remainingCell == 0) {
			end = clock();
			playTime += (double)(end - start) / CLOCKS_PER_SEC;

			account.time = int(playTime);
			account.isFinished = 1;
			account.score = gameplay.score;
			account.mode = 0;

			std::system("cls");
			Menu::winScreen(account);
			isPlaying = 0;
		}
		else if (gameplay.validPair == 0 && gameplay.remainingCell != 0) {
			Console::gotoXY(70, 5);
			std::cout << "OUT OF MOVE! SHUFFLING...";
			Sleep(1000);
			Console::gotoXY(70, 5);
			std::cout << "                         ";
			board.shuffle(HEIGHT, WIDTH, board.pBoard);
		}
	}

	const char* Username = account.UserName.c_str();

	ofstream ofs("Leaderboard\\leaderboard.bin", ios::out | ios::app | ios::binary);

	if (ofs) {
		ofs.write(reinterpret_cast<char*> (&account.Num), sizeof(int));
		ofs.write(Username, 20);
		ofs.write(reinterpret_cast<char*> (&account.mode), sizeof(int));
		ofs.write(reinterpret_cast<char*> (&account.score), sizeof(int));
		ofs.write(reinterpret_cast<char*> (&account.time), sizeof(int));

		ofs.close();
	}
	else {
		exit(1);
	}

	Board::clearBackground(background, HEIGHT);
	board.clearBoard(board.pBoard);
}

void GameMode::createHardGame_2DPointerArray(Account& account) {
	clock_t start, end;
	double playTime = 0;
	start = clock();

	Board board(H_TOP, H_LEFT, H_HEIGHT, H_WIDTH);
	GamePlay gameplay;
	gameplay.score = 0;
	pair<int, int> check(-2, -2);

	pair<int, int> selectedCell[2] = { { -2, -2}, {-2, -2} };
	int remainCell = 2;	// remaining Selectable Cells
	pair<int, int> curPos(0, 0);
	int isPlaying = 1; // 1 = đang chơi, 0 là hết game

	int key = 0;
	int EXIT = 0;

	char** background;
	Board::getBackground(background, H_HEIGHT, H_WIDTH, 1);

	while (isPlaying) {
		board.drawBoard(H_HEIGHT, H_WIDTH, board.pBoard);
		LoginScreen::printAccountName(account);

		if (gameplay.score < 0)
			gameplay.score = 0;
		gameplay.remainingCell = 0;
		gameplay.validPair = 0;

		//Count remainingCells
		for (int i = 0; i < H_HEIGHT; i++)
			for (int j = 0; j < H_WIDTH; j++)
				if (board.pBoard[i][j].pokemon != '0')
					gameplay.remainingCell += 1;


		//Count validPairs
		for (int i = 0; i < H_HEIGHT * H_WIDTH; i++) {
			if (board.pBoard[i / H_WIDTH][i % H_WIDTH].pokemon != '0')
				for (int j = i + 1; j < H_HEIGHT * H_WIDTH; j++) {
					if (board.pBoard[j / H_WIDTH][j % H_WIDTH].pokemon == board.pBoard[i / H_WIDTH][i % H_WIDTH].pokemon) {
						check = gameplay.check2Cells(board.pBoard, H_HEIGHT, H_WIDTH, board.pBoard[j / H_WIDTH][j % H_WIDTH], board.pBoard[i / H_WIDTH][i % H_WIDTH]);

						if (check.first != -2 || check.second != -2)
							gameplay.validPair += 1;

						check = make_pair(-2, -2);
					}
				}
		}

		//display some infos
		Console::gotoXY(65, 0);
		std::cout << "MODE: HARD";

		if (gameplay.score >= 10) {
			Console::gotoXY(85, 0);
			std::cout << "SCORE: " << gameplay.score;
		}
		else{
			Console::gotoXY(85, 0);
			std::cout << "SCORE: 0" << gameplay.score;
		}

		if (gameplay.remainingCell >= 10) {
			Console::gotoXY(100, 0);
			std::cout << "RemainingCell(s): " << gameplay.remainingCell;
		}
		else {
			Console::gotoXY(100, 0);
			std::cout << "RemainingCell(s): 0" << gameplay.remainingCell;
		}

		if (gameplay.validPair >= 10) {
			Console::gotoXY(125, 0);
			std::cout << "ValidPair(s): " << gameplay.validPair;
		}
		else {
			Console::gotoXY(125, 0);
			std::cout << "ValidPair(s): 0" << gameplay.validPair;
		}

		Menu::printDoubleRectangle(114, 2, 29, 2);
		Console::gotoXY(115, 3);
		std::cout << "Press I for more information.";

		//Draw selected Cell
		for (int i = 0; i < H_HEIGHT * H_WIDTH; i++)
			if (board.pBoard[i / H_WIDTH][i % H_WIDTH].isSelected)
				board.pBoard[i / H_WIDTH][i % H_WIDTH].drawCell(YELLOW);

		//Draw cell pointed by cursor
		board.pBoard[curPos.first][curPos.second].drawCell(LIGHT_RED);

		//Lặp các phím
		if (gameplay.remainingCell != 0) {
			while (true) {					//Xài trong trường hợp người dùng không nhập vào 1 trong các phím ở dưới
				bool true_while_flag = 0;	//Cờ thoát vòng lặp while true
				bool isCurFound = 0;
				key = _getch();

				switch (key) {
				case KEY_ESC:
					end = clock();
					playTime += (double)(end - start) / CLOCKS_PER_SEC;

					Console::playSound(MENU_SOUND);
					std::system("cls");
					EXIT = Menu::exitScreen();
					if (EXIT == 0) {
						true_while_flag = 0;
						Board::displayBackground(board.pBoard, background, H_HEIGHT, H_WIDTH);
						start = clock();
						break;
					}
					else
						exit(0);

				case KEY_RIGHT:
					Console::playSound(MOVE_SOUND);
					//Check về bên phải cùng hàng
					if (isCurFound == 0) {
						for (int j = curPos.second + 1; j < H_WIDTH; j++)
							if (board.pBoard[curPos.first][j].pokemon != '0') {
								isCurFound = 1;
								curPos.second = j;
								break;
							}
					}

					//Check theo đường xiên xuống 
					if (isCurFound == 0) {
						for (int i = curPos.first + 1; i < H_HEIGHT; i++) {
							for (int j = curPos.second + 1; j < H_WIDTH; j++) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//Check xiên lên
					if (isCurFound == 0) {
						for (int i = curPos.first - 1; i >= 0; i--) {
							for (int j = curPos.second + 1; j < H_WIDTH; j++) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//check ngược lại
					if (isCurFound == 0) {
						for (int j = 0; j < curPos.second; j++)
							if (board.pBoard[curPos.first][j].pokemon != '0') {
								isCurFound = 1;
								curPos.second = j;
								break;
							}
					}

					break;

				case KEY_LEFT:
					Console::playSound(MOVE_SOUND);
					//Check về bên trái cùng hàng
					if (isCurFound == 0) {
						for (int j = curPos.second - 1; j >= 0; j--)
							if (board.pBoard[curPos.first][j].pokemon != '0') {
								isCurFound = 1;
								curPos.second = j;
								break;
							}
					}

					//Check theo đường xiên xuống 
					if (isCurFound == 0) {
						for (int i = curPos.first + 1; i < H_HEIGHT; i++) {
							for (int j = curPos.second - 1; j >= 0; j--) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//Check xiên lên
					if (isCurFound == 0) {
						for (int i = curPos.first - 1; i >= 0; i--) {
							for (int j = curPos.second - 1; j >= 0; j--) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//check ngược lại
					if (isCurFound == 0) {
						for (int j = H_WIDTH - 1; j > curPos.second; j--)
							if (board.pBoard[curPos.first][j].pokemon != '0') {
								isCurFound = 1;
								curPos.second = j;
								break;
							}
					}
					break;

				case KEY_DOWN:
					Console::playSound(MOVE_SOUND);
					//Check thẳng xuống
					if (isCurFound == 0) {
						for (int i = curPos.first + 1; i < H_HEIGHT; i++)
							if (board.pBoard[i][curPos.second].pokemon != '0') {
								isCurFound = 1;
								curPos.first = i;
								break;
							}
					}

					//Check theo đường xiên xuống qua phải
					if (isCurFound == 0) {
						for (int j = curPos.second + 1; j < H_WIDTH; j++) {
							for (int i = curPos.first + 1; i < H_HEIGHT; i++) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//Check xiên xuống qua trái
					if (isCurFound == 0) {
						for (int j = curPos.second - 1; j >= 0; j--) {
							for (int i = curPos.first + 1; i < H_HEIGHT; i++) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//check ngược lại
					if (isCurFound == 0) {
						for (int i = 0; i < curPos.first; i++)
							if (board.pBoard[i][curPos.second].pokemon != '0') {
								isCurFound = 1;
								curPos.first = i;
								break;
							}
					}
					break;

				case KEY_UP:
					Console::playSound(MOVE_SOUND);
					//Check lên trên
					if (isCurFound == 0) {
						for (int i = curPos.first - 1; i >= 0; i--)
							if (board.pBoard[i][curPos.second].pokemon != '0') {
								isCurFound = 1;
								curPos.first = i;
								break;
							}
					}

					//Check theo đường xiên lên qua phải
					if (isCurFound == 0) {
						for (int j = curPos.second + 1; j < H_WIDTH; j++) {
							for (int i = curPos.first - 1; i >= 0; i--) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//Check xiên lên qua trái
					if (isCurFound == 0) {
						for (int j = curPos.second - 1; j >= 0; j--) {
							for (int i = curPos.first - 1; i > 0; i--) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//check ngược lại
					if (isCurFound == 0) {
						for (int i = H_HEIGHT - 1; i > curPos.first; i--)
							if (board.pBoard[i][curPos.second].pokemon != '0') {
								isCurFound = 1;
								curPos.first = i;
								break;
							}
					}
					break;

				case KEY_ENTER:
					//Nếu ô đã chọn hay chưa chọn
					if (board.pBoard[curPos.first][curPos.second].isSelected == 0)
						board.pBoard[curPos.first][curPos.second].isSelected = 1;
					else
						board.pBoard[curPos.first][curPos.second].isSelected = 0;

					//Nếu chọn
					if (board.pBoard[curPos.first][curPos.second].isSelected == 1) {
						remainCell--;
						board.pBoard[curPos.first][curPos.second].drawCell(YELLOW);

						if (remainCell == 1) {
							selectedCell[0].first = curPos.first;
							selectedCell[0].second = curPos.second;
						}
						else if (remainCell == 0) {
							selectedCell[1].first = curPos.first;
							selectedCell[1].second = curPos.second;
						}

						if (remainCell == 0) {	//Nếu đã chọn dược 2 cell
							Sleep(250);
							check = gameplay.check2Cells(board.pBoard, H_HEIGHT, H_WIDTH, board.pBoard[selectedCell[0].first][selectedCell[0].second], board.pBoard[selectedCell[1].first][selectedCell[1].second]);

							if (check.first != -2 || check.second != -2) {
								gameplay.score += 2;
								Console::playSound(MOVE_SOUND);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].drawCell(GREEN);
								board.pBoard[selectedCell[1].first][selectedCell[1].second].drawCell(GREEN);
								gameplay.drawLine2Cells(board.pBoard, HEIGHT, WIDTH, TOP, LEFT, board.pBoard[selectedCell[0].first][selectedCell[0].second], board.pBoard[selectedCell[1].first][selectedCell[1].second]);
								Console::setColor(WHITE, BLACK);
								Sleep(500);

								gameplay.eraseLine2Cells(board.pBoard, HEIGHT, WIDTH, TOP, LEFT, board.pBoard[selectedCell[0].first][selectedCell[0].second], board.pBoard[selectedCell[1].first][selectedCell[1].second]);
								Console::setColor(WHITE, BLACK);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].deleteCell();
								board.pBoard[selectedCell[1].first][selectedCell[1].second].deleteCell();

								board.pBoard[selectedCell[0].first][selectedCell[0].second].isSelected = 0;
								board.pBoard[selectedCell[1].first][selectedCell[1].second].isSelected = 0;

								if (selectedCell[0].second < selectedCell[1].second) {	//Nếu cell được chọn sau nằm về bên phải cell được chọn đầu
									int i = selectedCell[1].second;
									while (board.pBoard[selectedCell[1].first][i + 1].pokemon != '0' && i < H_WIDTH - 1) {
										board.pBoard[selectedCell[1].first][i].pokemon = board.pBoard[selectedCell[1].first][i + 1].pokemon;
										i++;
									}
									board.pBoard[selectedCell[1].first][i].pokemon = '0';
									board.pBoard[selectedCell[1].first][i].deleteCell();
									i = 0;
									i = selectedCell[0].second;
									while (board.pBoard[selectedCell[0].first][i + 1].pokemon != '0' && i < H_WIDTH - 1) {
										board.pBoard[selectedCell[0].first][i].pokemon = board.pBoard[selectedCell[0].first][i + 1].pokemon;
										i++;
									}
									board.pBoard[selectedCell[0].first][i].pokemon = '0';
									board.pBoard[selectedCell[0].first][i].deleteCell();
								}
								else {
									int i = selectedCell[0].second;
									while (board.pBoard[selectedCell[0].first][i + 1].pokemon != '0' && i < H_WIDTH - 1) {
										board.pBoard[selectedCell[0].first][i].pokemon = board.pBoard[selectedCell[0].first][i + 1].pokemon;
										i++;
									}
									board.pBoard[selectedCell[0].first][i].pokemon = '0';
									board.pBoard[selectedCell[0].first][i].deleteCell();
									i = 0;
									i = selectedCell[1].second;
									while (board.pBoard[selectedCell[1].first][i + 1].pokemon != '0' && i < H_WIDTH - 1) {
										board.pBoard[selectedCell[1].first][i].pokemon = board.pBoard[selectedCell[1].first][i + 1].pokemon;
										i++;
									}
									board.pBoard[selectedCell[1].first][i].pokemon = '0';
									board.pBoard[selectedCell[1].first][i].deleteCell();
								}


								Board::displayBackground(board.pBoard, background, HEIGHT, WIDTH);
								remainCell = 2;
								selectedCell[0].first = -2;
								selectedCell[0].second = -2;
								selectedCell[1].first = -2;
								selectedCell[1].second = -2;
							}
							else {
								Console::playSound(ERROR_SOUND);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].drawCell(RED);
								board.pBoard[selectedCell[1].first][selectedCell[1].second].drawCell(RED);
								Sleep(500);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].drawCell(WHITE);
								board.pBoard[selectedCell[1].first][selectedCell[1].second].drawCell(WHITE);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].isSelected = 0;
								board.pBoard[selectedCell[1].first][selectedCell[1].second].isSelected = 0;

								remainCell = 2;
								selectedCell[0].first = -2;
								selectedCell[0].second = -2;
								selectedCell[1].first = -2;
								selectedCell[1].second = -2;
							}

							check = make_pair(-2, -2);
						}

					}

					//Nếu bỏ chọn
					else {
						remainCell++;

						board.pBoard[selectedCell[0].first][selectedCell[0].second].isSelected = 0;

						selectedCell[0].first = -2;
						selectedCell[0].second = -2;
					}
					break;
				case 'S':
					Console::playSound(MENU_SOUND);
					gameplay.score -= 2;
					Console::gotoXY(70, 5);
					std::cout << "SHUFFLING...";
					Sleep(1000);
					Console::gotoXY(70, 5);
					std::cout << "            ";

					board.shuffle(H_HEIGHT, H_WIDTH, board.pBoard);
					break;
				case 's':
					Console::playSound(MENU_SOUND);
					gameplay.score -= 2;
					Console::gotoXY(70, 5);
					std::cout << "SHUFFLING...";
					Sleep(1000);
					Console::gotoXY(70, 5);
					std::cout << "            ";

					board.shuffle(H_HEIGHT, H_WIDTH, board.pBoard);
					break;
				case 'A':
					Console::playSound(MENU_SOUND);
					gameplay.score -= 2;
					moveSuggestion(HEIGHT, WIDTH, board.pBoard);
					Sleep(500);
					break;
				case 'a':
					Console::playSound(MENU_SOUND);
					gameplay.score -= 2;
					moveSuggestion(HEIGHT, WIDTH, board.pBoard);
					Sleep(500);
					break;
				case 'I':
					end = clock();
					playTime += (double)(end - start) / CLOCKS_PER_SEC;

					Console::playSound(MENU_SOUND);
					Console::clearConsole();
					Console::setColor(WHITE, BLUE);
					Console::gotoXY(57, 0);
					std::cout << "Play time up to now: " << playTime << "s...";
					Console::setColor(WHITE, BLACK);

					Menu::helpScreen();

					Board::displayBackground(board.pBoard, background, H_HEIGHT, H_WIDTH);
					start = clock();
					break;
				case 'i':
					end = clock();
					playTime += (double)(end - start) / CLOCKS_PER_SEC;

					Console::playSound(MENU_SOUND);
					Console::clearConsole();
					Console::setColor(WHITE, BLUE);
					Console::gotoXY(57, 0);
					std::cout << "Play time up to now: " << playTime << "s...";
					Console::setColor(WHITE, BLACK);

					Menu::helpScreen();

					Board::displayBackground(board.pBoard, background, H_HEIGHT, H_WIDTH);
					start = clock();
					break;
				default:
					true_while_flag = 1;
					break;
				}
				if (true_while_flag == 0)
					break;
			}
		}
		else {
			Sleep(500);
		}

		if (gameplay.validPair == 0 && gameplay.remainingCell == 0) {
			end = clock();
			playTime += (double)(end - start) / CLOCKS_PER_SEC;

			account.time = int(playTime);
			account.isFinished = 1;
			account.score = gameplay.score;
			account.mode = 1;

			std::system("cls");
			Menu::winScreen(account);
			isPlaying = 0;
		}
		else if (gameplay.validPair == 0 && gameplay.remainingCell != 0) {
			Console::gotoXY(70, 5);
			std::cout << "OUT OF MOVE! SHUFFLING...";
			Sleep(1000);
			Console::gotoXY(70, 5);
			std::cout << "                         ";
			board.shuffle(HEIGHT, WIDTH, board.pBoard);
		}
	}

	const char* Username = account.UserName.c_str();

	ofstream ofs("Leaderboard\\leaderboard.bin", ios::out | ios::app | ios::binary);

	if (ofs) {
		ofs.write(reinterpret_cast<char*> (&account.Num), sizeof(int));
		ofs.write(Username, 20);
		ofs.write(reinterpret_cast<char*> (&account.mode), sizeof(int));
		ofs.write(reinterpret_cast<char*> (&account.score), sizeof(int));
		ofs.write(reinterpret_cast<char*> (&account.time), sizeof(int));

		ofs.close();
	}
	else {
		exit(1);
	}

	Board::clearBackground(background, HEIGHT);
	board.clearBoard(board.pBoard);
}

void GameMode::createHardGame_LinkedList(Account& account) {
	clock_t start, end;
	double playTime = 0;
	start = clock();

	Board board(H_TOP, H_LEFT, H_HEIGHT, H_WIDTH);
	GamePlay gameplay;
	gameplay.score = 0;
	pair<int, int> check(-2, -2);

	pair<int, int> selectedCell[2] = { { -2, -2}, {-2, -2} };
	int remainCell = 2;	// remaining Selectable Cells
	pair<int, int> curPos(0, 0);
	int isPlaying = 1; // 1 = đang chơi, 0 là hết game

	int key = 0;
	int EXIT = 0;

	char** background;
	Board::getBackground(background, H_HEIGHT, H_WIDTH, 1);

	//Tạo linked list
	Node* head = createNode(board.pBoard[0][0].pokemon, board.pBoard[0][0].x, board.pBoard[0][0].y);
	for (int i = 1; i < H_HEIGHT * H_WIDTH; i++) {
		addTail(head, board.pBoard[i / H_WIDTH][i % H_WIDTH].pokemon, board.pBoard[i / H_WIDTH][i % H_WIDTH].x, board.pBoard[i / H_WIDTH][i % H_WIDTH].y);
	}

	//Dùng khi shuffle để tránh lỗi multiple init
	Node* tempo = NULL;
	int len = 0;

	while (isPlaying) {
		board.drawBoard(H_HEIGHT, H_WIDTH, board.pBoard);	//Vẽ board hiện tại
		LoginScreen::printAccountName(account);

		if (gameplay.score < 0)
			gameplay.score = 0;
		gameplay.remainingCell = 0;
		gameplay.validPair = 0;

		//Count remainingCells
		for (int i = 0; i < H_HEIGHT; i++)
			for (int j = 0; j < H_WIDTH; j++)
				if (board.pBoard[i][j].pokemon != '0')
					gameplay.remainingCell += 1;


		//Count validPairs
		for (int i = 0; i < H_HEIGHT * H_WIDTH; i++) {
			if (board.pBoard[i / H_WIDTH][i % H_WIDTH].pokemon != '0')
				for (int j = i + 1; j < H_HEIGHT * H_WIDTH; j++) {
					if (board.pBoard[j / H_WIDTH][j % H_WIDTH].pokemon == board.pBoard[i / H_WIDTH][i % H_WIDTH].pokemon) {
						check = gameplay.check2Cells(board.pBoard, H_HEIGHT, H_WIDTH, board.pBoard[j / H_WIDTH][j % H_WIDTH], board.pBoard[i / H_WIDTH][i % H_WIDTH]);

						if (check.first != -2 || check.second != -2)
							gameplay.validPair += 1;

						check = make_pair(-2, -2);
					}
				}
		}

		//display some infos
		Console::gotoXY(65, 0);
		std::cout << "MODE: HARD";

		if (gameplay.score >= 10) {
			Console::gotoXY(85, 0);
			std::cout << "SCORE: " << gameplay.score;
		}
		else {
			Console::gotoXY(85, 0);
			std::cout << "SCORE: 0" << gameplay.score;
		}

		if (gameplay.remainingCell >= 10) {
			Console::gotoXY(100, 0);
			std::cout << "RemainingCell(s): " << gameplay.remainingCell;
		}
		else {
			Console::gotoXY(100, 0);
			std::cout << "RemainingCell(s): 0" << gameplay.remainingCell;
		}

		if (gameplay.validPair >= 10) {
			Console::gotoXY(125, 0);
			std::cout << "ValidPair(s): " << gameplay.validPair;
		}
		else {
			Console::gotoXY(125, 0);
			std::cout << "ValidPair(s): 0" << gameplay.validPair;
		}

		Menu::printDoubleRectangle(114, 2, 29, 2);
		Console::gotoXY(115, 3);
		std::cout << "Press I for more information.";

		//Draw selected Cell
		for (int i = 0; i < H_HEIGHT * H_WIDTH; i++)
			if (board.pBoard[i / H_WIDTH][i % H_WIDTH].isSelected)
				board.pBoard[i / H_WIDTH][i % H_WIDTH].drawCell(YELLOW);

		//Draw cell pointed by cursor
		board.pBoard[curPos.first][curPos.second].drawCell(LIGHT_RED);

		//Lặp các phím
		if (gameplay.remainingCell != 0) {
			while (true) {					//Xài trong trường hợp người dùng không nhập vào 1 trong các phím ở dưới
				bool true_while_flag = 0;	//Cờ thoát vòng lặp while true
				bool isCurFound = 0;
				key = _getch();

				switch (key) {
				case KEY_ESC:
					end = clock();
					playTime += (double)(end - start) / CLOCKS_PER_SEC;

					Console::playSound(MENU_SOUND);
					std::system("cls");
					EXIT = Menu::exitScreen();
					if (EXIT == 0) {
						true_while_flag = 0;
						Board::displayBackground(board.pBoard, background, H_HEIGHT, H_WIDTH);
						start = clock();
						break;
					}
					else
						exit(0);

				case KEY_RIGHT:
					Console::playSound(MOVE_SOUND);
					//Check về bên phải cùng hàng
					if (isCurFound == 0) {
						for (int j = curPos.second + 1; j < H_WIDTH; j++)
							if (board.pBoard[curPos.first][j].pokemon != '0') {
								isCurFound = 1;
								curPos.second = j;
								break;
							}
					}

					//Check theo đường xiên xuống 
					if (isCurFound == 0) {
						for (int i = curPos.first + 1; i < H_HEIGHT; i++) {
							for (int j = curPos.second + 1; j < H_WIDTH; j++) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//Check xiên lên
					if (isCurFound == 0) {
						for (int i = curPos.first - 1; i >= 0; i--) {
							for (int j = curPos.second + 1; j < H_WIDTH; j++) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//check ngược lại
					if (isCurFound == 0) {
						for (int j = 0; j < curPos.second; j++)
							if (board.pBoard[curPos.first][j].pokemon != '0') {
								isCurFound = 1;
								curPos.second = j;
								break;
							}
					}

					break;

				case KEY_LEFT:
					Console::playSound(MOVE_SOUND);
					//Check về bên trái cùng hàng
					if (isCurFound == 0) {
						for (int j = curPos.second - 1; j >= 0; j--)
							if (board.pBoard[curPos.first][j].pokemon != '0') {
								isCurFound = 1;
								curPos.second = j;
								break;
							}
					}

					//Check theo đường xiên xuống 
					if (isCurFound == 0) {
						for (int i = curPos.first + 1; i < H_HEIGHT; i++) {
							for (int j = curPos.second - 1; j >= 0; j--) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//Check xiên lên
					if (isCurFound == 0) {
						for (int i = curPos.first - 1; i >= 0; i--) {
							for (int j = curPos.second - 1; j >= 0; j--) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//check ngược lại
					if (isCurFound == 0) {
						for (int j = H_WIDTH - 1; j > curPos.second; j--)
							if (board.pBoard[curPos.first][j].pokemon != '0') {
								isCurFound = 1;
								curPos.second = j;
								break;
							}
					}
					break;

				case KEY_DOWN:
					Console::playSound(MOVE_SOUND);
					//Check thẳng xuống
					if (isCurFound == 0) {
						for (int i = curPos.first + 1; i < H_HEIGHT; i++)
							if (board.pBoard[i][curPos.second].pokemon != '0') {
								isCurFound = 1;
								curPos.first = i;
								break;
							}
					}

					//Check theo đường xiên xuống qua phải
					if (isCurFound == 0) {
						for (int j = curPos.second + 1; j < H_WIDTH; j++) {
							for (int i = curPos.first + 1; i < H_HEIGHT; i++) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//Check xiên xuống qua trái
					if (isCurFound == 0) {
						for (int j = curPos.second - 1; j >= 0; j--) {
							for (int i = curPos.first + 1; i < H_HEIGHT; i++) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//check ngược lại
					if (isCurFound == 0) {
						for (int i = 0; i < curPos.first; i++)
							if (board.pBoard[i][curPos.second].pokemon != '0') {
								isCurFound = 1;
								curPos.first = i;
								break;
							}
					}
					break;

				case KEY_UP:
					Console::playSound(MOVE_SOUND);
					//Check lên trên
					if (isCurFound == 0) {
						for (int i = curPos.first - 1; i >= 0; i--)
							if (board.pBoard[i][curPos.second].pokemon != '0') {
								isCurFound = 1;
								curPos.first = i;
								break;
							}
					}

					//Check theo đường xiên lên qua phải
					if (isCurFound == 0) {
						for (int j = curPos.second + 1; j < H_WIDTH; j++) {
							for (int i = curPos.first - 1; i >= 0; i--) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//Check xiên lên qua trái
					if (isCurFound == 0) {
						for (int j = curPos.second - 1; j >= 0; j--) {
							for (int i = curPos.first - 1; i > 0; i--) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//check ngược lại
					if (isCurFound == 0) {
						for (int i = H_HEIGHT - 1; i > curPos.first; i--)
							if (board.pBoard[i][curPos.second].pokemon != '0') {
								isCurFound = 1;
								curPos.first = i;
								break;
							}
					}
					break;

				case KEY_ENTER:
					//Nếu ô đã chọn hay chưa chọn
					if (board.pBoard[curPos.first][curPos.second].isSelected == 0)
						board.pBoard[curPos.first][curPos.second].isSelected = 1;
					else
						board.pBoard[curPos.first][curPos.second].isSelected = 0;

					//Nếu chọn
					if (board.pBoard[curPos.first][curPos.second].isSelected == 1) {
						remainCell--;
						board.pBoard[curPos.first][curPos.second].drawCell(YELLOW);

						if (remainCell == 1) {
							selectedCell[0].first = curPos.first;
							selectedCell[0].second = curPos.second;
						}
						else if (remainCell == 0) {
							selectedCell[1].first = curPos.first;
							selectedCell[1].second = curPos.second;
						}

						if (remainCell == 0) {	//Nếu đã chọn dược 2 cell
							Sleep(250);
							check = gameplay.check2Cells(board.pBoard, H_HEIGHT, H_WIDTH, board.pBoard[selectedCell[0].first][selectedCell[0].second], board.pBoard[selectedCell[1].first][selectedCell[1].second]);

							if (check.first != -2 || check.second != -2) { //Nếu đúng
								gameplay.score += 2;
								Console::playSound(MOVE_SOUND);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].drawCell(GREEN);
								board.pBoard[selectedCell[1].first][selectedCell[1].second].drawCell(GREEN);
								gameplay.drawLine2Cells(board.pBoard, H_HEIGHT, H_WIDTH, H_TOP, H_LEFT, board.pBoard[selectedCell[0].first][selectedCell[0].second], board.pBoard[selectedCell[1].first][selectedCell[1].second]);
								Console::setColor(WHITE, BLACK);
								Sleep(500);

								gameplay.eraseLine2Cells(board.pBoard, H_HEIGHT, H_WIDTH, H_TOP, H_LEFT, board.pBoard[selectedCell[0].first][selectedCell[0].second], board.pBoard[selectedCell[1].first][selectedCell[1].second]);
								Console::setColor(WHITE, BLACK);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].deleteCell();
								board.pBoard[selectedCell[1].first][selectedCell[1].second].deleteCell();

								board.pBoard[selectedCell[0].first][selectedCell[0].second].isSelected = 0;
								board.pBoard[selectedCell[1].first][selectedCell[1].second].isSelected = 0;

								//Đặt key 2 node được chọn là '1'
								Node* node_0 = getNode(head, selectedCell[0].first * H_WIDTH + selectedCell[0].second);
								Node* node_1 = getNode(head, selectedCell[1].first * H_WIDTH + selectedCell[1].second);
								node_0->key = '1';
								node_1->key = '1';

								//Lấy node đầu hàng của 2 node được chọn
								Node* selectedCell_0 = getNode(head, selectedCell[0].first * H_WIDTH);
								Node* selectedCell_1 = getNode(head, selectedCell[1].first * H_WIDTH);

								//Duyệt hàng có node được chọn
								while ((selectedCell_0->pNext != NULL && selectedCell_0->pNext->x == selectedCell_0->x ) || selectedCell_0->y == H_WIDTH - 1) {
									if (selectedCell_0->key == '1') {//selectedCell_0 là node cần xóa

										while ((selectedCell_0->pNext != NULL && selectedCell_0->pNext->x == selectedCell_0->x)) {//Duyệt đến cuối hàng từ vị trí được chọn
											selectedCell_0->key = selectedCell_0->pNext->key;	//Gán tuần tự
											selectedCell_0 = selectedCell_0->pNext;
										}

										//SelectedCell_0 lúc này là node cuối hàng
										selectedCell_0->key = '0';
										break;
									}

									selectedCell_0 = selectedCell_0->pNext;
								}

								while ((selectedCell_1->pNext != NULL && selectedCell_1->pNext->x == selectedCell_1->x) || selectedCell_1->y == H_WIDTH - 1) {
									if (selectedCell_1->key == '1') {//selectedCell_1 là node cần xóa

										while ((selectedCell_1->pNext != NULL && selectedCell_1->pNext->x == selectedCell_1->x)) {//Duyệt đến cuối hàng từ vị trí được chọn
											selectedCell_1->key = selectedCell_1->pNext->key;	//Gán tuần tự
											selectedCell_1 = selectedCell_1->pNext;
										}

										//SelectedCell_0 lúc này là node cuối hàng
										selectedCell_1->key = '0';
										break;
									}

									selectedCell_1 = selectedCell_1->pNext;
								}

								//Chép vào board
								tempo = head;
								len = 0;
								while (tempo != NULL && len < H_WIDTH * H_HEIGHT) {
									board.pBoard[len / H_WIDTH][len % H_WIDTH].pokemon = tempo->key;
									len++;
									tempo = tempo->pNext;
								}

								//Xóa cell trống
								for (int i = 0; i < H_HEIGHT * H_WIDTH; i++) {
									if (board.pBoard[i / H_WIDTH][i % H_WIDTH].pokemon == '0') {
										board.pBoard[i / H_WIDTH][i % H_WIDTH].deleteCell();
									}
								}

								Board::displayBackground(board.pBoard, background, HEIGHT, WIDTH);

								//Đặt lại
								remainCell = 2;
								selectedCell[0].first = -2;
								selectedCell[0].second = -2;
								selectedCell[1].first = -2;
								selectedCell[1].second = -2;
							}
							else {
								Console::playSound(ERROR_SOUND);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].drawCell(RED);
								board.pBoard[selectedCell[1].first][selectedCell[1].second].drawCell(RED);
								Sleep(500);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].drawCell(WHITE);
								board.pBoard[selectedCell[1].first][selectedCell[1].second].drawCell(WHITE);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].isSelected = 0;
								board.pBoard[selectedCell[1].first][selectedCell[1].second].isSelected = 0;

								remainCell = 2;
								selectedCell[0].first = -2;
								selectedCell[0].second = -2;
								selectedCell[1].first = -2;
								selectedCell[1].second = -2;
							}

							check = make_pair(-2, -2);
						}

					}

					//Nếu bỏ chọn
					else {
						remainCell++;

						board.pBoard[selectedCell[0].first][selectedCell[0].second].isSelected = 0;

						selectedCell[0].first = -2;
						selectedCell[0].second = -2;
					}
					break;
				case 'S':
					Console::playSound(MENU_SOUND);
					gameplay.score -= 2;
					Console::gotoXY(70, 5);
					std::cout << "SHUFFLING...";
					Sleep(1000);
					Console::gotoXY(70, 5);
					std::cout << "            ";

					board.shuffle(H_HEIGHT, H_WIDTH, board.pBoard);

					//Chép lại data vào head
					tempo = head;
					len = 0;
					while (tempo != NULL && len < H_WIDTH * H_HEIGHT) {
						tempo->key = board.pBoard[len / H_WIDTH][len % H_WIDTH].pokemon;
						len++;
						tempo = tempo->pNext;
					}

					break;
				case 's':
					Console::playSound(MENU_SOUND);
					gameplay.score -= 2;
					Console::gotoXY(70, 5);
					std::cout << "SHUFFLING...";
					Sleep(1000);
					Console::gotoXY(70, 5);
					std::cout << "            ";

					board.shuffle(H_HEIGHT, H_WIDTH, board.pBoard);
					tempo = head;
					len = 0;
					while (tempo != NULL && len < H_WIDTH * H_HEIGHT) {
						tempo->key = board.pBoard[len / WIDTH][len % WIDTH].pokemon;
						len++;
						tempo = tempo->pNext;
					}

					break;
				case 'A':
					Console::playSound(MENU_SOUND);
					gameplay.score -= 2;
					moveSuggestion(HEIGHT, WIDTH, board.pBoard);
					Sleep(500);
					break;
				case 'a':
					Console::playSound(MENU_SOUND);
					gameplay.score -= 2;
					moveSuggestion(HEIGHT, WIDTH, board.pBoard);
					Sleep(500);
					break;
				case 'I':
					end = clock();
					playTime += (double)(end - start) / CLOCKS_PER_SEC;

					Console::playSound(MENU_SOUND);
					Console::clearConsole();
					Console::setColor(WHITE, BLUE);
					Console::gotoXY(57, 0);
					std::cout << "Play time up to now: " << playTime << "s...";
					Console::setColor(WHITE, BLACK);

					Menu::helpScreen();

					Board::displayBackground(board.pBoard, background, H_HEIGHT, H_WIDTH);
					start = clock();
					break;
				case 'i':
					end = clock();
					playTime += (double)(end - start) / CLOCKS_PER_SEC;

					Console::playSound(MENU_SOUND);
					Console::clearConsole();
					Console::setColor(WHITE, BLUE);
					Console::gotoXY(57, 0);
					std::cout << "Play time up to now: " << playTime << "s...";
					Console::setColor(WHITE, BLACK);

					Menu::helpScreen();

					Board::displayBackground(board.pBoard, background, H_HEIGHT, H_WIDTH);
					start = clock();
					break;
				default:
					true_while_flag = 1;
					break;
				}
				if (true_while_flag == 0)
					break;
			}
		}
		else {
			Sleep(500);
		}

		if (gameplay.validPair == 0 && gameplay.remainingCell == 0) {
			end = clock();
			playTime += (double)(end - start) / CLOCKS_PER_SEC;

			account.time = int(playTime);
			account.isFinished = 1;
			account.score = gameplay.score;
			account.mode = 1;

			std::system("cls");
			Menu::winScreen(account);
			isPlaying = 0;
		}
		else if (gameplay.validPair == 0 && gameplay.remainingCell != 0) {
			Console::gotoXY(70, 5);
			std::cout << "OUT OF MOVE! SHUFFLING...";
			Sleep(1000);
			Console::gotoXY(70, 5);
			std::cout << "                         ";
			board.shuffle(H_HEIGHT, H_WIDTH, board.pBoard);

			tempo = head;
			len = 0;
			while (tempo != NULL && len < H_WIDTH * H_HEIGHT) {
				tempo->key = board.pBoard[len / H_WIDTH][len % H_WIDTH].pokemon;
				len++;
				tempo = tempo->pNext;
			}
		}
	}

	//Num/name/mode/score/time
	const char* Username = account.UserName.c_str();

	ofstream ofs("Leaderboard\\leaderboard.bin", ios::out | ios::app | ios::binary);

	if (ofs) {
		ofs.write(reinterpret_cast<char*> (&account.Num), sizeof(int));
		ofs.write(Username, 20);
		ofs.write(reinterpret_cast<char*> (&account.mode), sizeof(int));
		ofs.write(reinterpret_cast<char*> (&account.score), sizeof(int));
		ofs.write(reinterpret_cast<char*> (&account.time), sizeof(int));

		ofs.close();
	}
	else {
		exit(1);
	}

	deleteLinkedList(head);
	Board::clearBackground(background, HEIGHT);
	board.clearBoard(board.pBoard);
}

void GameMode::createCustomGame(Account& account, int height, int width, int mode) {
	clock_t start, end;
	double playTime = 0;
	start = clock();

	Board board(TOP, LEFT, height, width);
	GamePlay gameplay;
	gameplay.score = 0;
	pair<int, int> check(-2, -2);

	pair<int, int> selectedCell[2] = { { -2, -2}, {-2, -2} };
	int remainCell = 2;	// remaining Selectable Cells
	pair<int, int> curPos(0, 0);
	int isPlaying = 1; // 1 = đang chơi, 0 là hết game

	int key = 0;
	int EXIT = 0;

	char** background;
	Board::getBackground(background, height, width, mode);

	while (isPlaying) {
		board.drawBoard(height, width, board.pBoard);				//Vẽ board hiện tại
		LoginScreen::printAccountName(account);

		if (gameplay.score < 0)
			gameplay.score = 0;
		gameplay.remainingCell = 0;
		gameplay.validPair = 0;

		//Count remainingCells
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				if (board.pBoard[i][j].pokemon != '0')
					gameplay.remainingCell += 1;

		//Count validPairs
		for (int i = 0; i < height * width; i++) {
			if (board.pBoard[i / width][i % width].pokemon != '0')
				for (int j = i + 1; j < height * width; j++) {
					if (board.pBoard[j / width][j % width].pokemon == board.pBoard[i / width][i % width].pokemon) {
						check = gameplay.check2Cells(board.pBoard, height, width, board.pBoard[j / width][j % width], board.pBoard[i / width][i % width]);

						if (check.first != -2 || check.second != -2)
							gameplay.validPair += 1;

						check = make_pair(-2, -2);
					}
				}
		}

		//display some infos
		Console::gotoXY(65, 0);
		std::cout << "MODE: CUSTOM";
		if (gameplay.score >= 10) {
			Console::gotoXY(85, 0);
			std::cout << "SCORE: " << gameplay.score;
		}
		else {
			Console::gotoXY(85, 0);
			std::cout << "SCORE: 0" << gameplay.score;
		}
		if (gameplay.remainingCell >= 10) {
			Console::gotoXY(100, 0);
			std::cout << "RemainingCell(s): " << gameplay.remainingCell;
		}
		else {
			Console::gotoXY(100, 0);
			std::cout << "RemainingCell(s): 0" << gameplay.remainingCell;
		}

		if (gameplay.validPair >= 10) {
			Console::gotoXY(125, 0);
			std::cout << "ValidPair(s): " << gameplay.validPair;
		}
		else {
			Console::gotoXY(125, 0);
			std::cout << "ValidPair(s): 0" << gameplay.validPair;
		}

		Menu::printDoubleRectangle(114, 2, 29, 2);
		Console::gotoXY(115, 3);
		std::cout << "Press I for more information.";

		//Draw selected Cell
		for (int i = 0; i < height * width; i++)
			if (board.pBoard[i / width][i % width].isSelected)
				board.pBoard[i / width][i % width].drawCell(YELLOW);

		//Draw cell pointed by cursor
		board.pBoard[curPos.first][curPos.second].drawCell(LIGHT_RED);

		//Lặp các phím
		if (gameplay.remainingCell != 0) {
			while (true) {					//Xài trong trường hợp người dùng không nhập vào 1 trong các phím ở dưới
				bool true_while_flag = 0;	//Cờ thoát vòng lặp while true
				bool isCurFound = 0;
				key = _getch();

				switch (key) {
				case KEY_ESC:
					end = clock();
					playTime += (double)(end - start) / CLOCKS_PER_SEC;

					Console::playSound(MENU_SOUND);
					std::system("cls");
					EXIT = Menu::exitScreen();
					if (EXIT == 0) {
						true_while_flag = 0;
						Board::displayBackground(board.pBoard, background, height, width);

						start = clock();
						break;
					}
					else {
						Board::clearBackground(background, height);
						board.clearBoard(board.pBoard);
						exit(0);
					}
				case KEY_RIGHT:
					Console::playSound(MOVE_SOUND);
					//Check về bên phải cùng hàng
					if (isCurFound == 0) {
						for (int j = curPos.second + 1; j < width; j++)
							if (board.pBoard[curPos.first][j].pokemon != '0') {
								isCurFound = 1;
								curPos.second = j;
								break;
							}
					}

					//Check theo đường xiên xuống 
					if (isCurFound == 0) {
						for (int i = curPos.first + 1; i < height; i++) {
							for (int j = curPos.second + 1; j < width; j++) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//Check xiên lên
					if (isCurFound == 0) {
						for (int i = curPos.first - 1; i >= 0; i--) {
							for (int j = curPos.second + 1; j < width; j++) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//check ngược lại
					if (isCurFound == 0) {
						for (int j = 0; j < curPos.second; j++)
							if (board.pBoard[curPos.first][j].pokemon != '0') {
								isCurFound = 1;
								curPos.second = j;
								break;
							}
					}

					break;

				case KEY_LEFT:
					Console::playSound(MOVE_SOUND);
					//Check về bên trái cùng hàng
					if (isCurFound == 0) {
						for (int j = curPos.second - 1; j >= 0; j--)
							if (board.pBoard[curPos.first][j].pokemon != '0') {
								isCurFound = 1;
								curPos.second = j;
								break;
							}
					}

					//Check theo đường xiên xuống 
					if (isCurFound == 0) {
						for (int i = curPos.first + 1; i < height; i++) {
							for (int j = curPos.second - 1; j >= 0; j--) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//Check xiên lên
					if (isCurFound == 0) {
						for (int i = curPos.first - 1; i >= 0; i--) {
							for (int j = curPos.second - 1; j >= 0; j--) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//check ngược lại
					if (isCurFound == 0) {
						for (int j = width - 1; j > curPos.second; j--)
							if (board.pBoard[curPos.first][j].pokemon != '0') {
								isCurFound = 1;
								curPos.second = j;
								break;
							}
					}
					break;

				case KEY_DOWN:
					Console::playSound(MOVE_SOUND);
					//Check thẳng xuống
					if (isCurFound == 0) {
						for (int i = curPos.first + 1; i < height; i++)
							if (board.pBoard[i][curPos.second].pokemon != '0') {
								isCurFound = 1;
								curPos.first = i;
								break;
							}
					}

					//Check theo đường xiên xuống qua phải
					if (isCurFound == 0) {
						for (int j = curPos.second + 1; j < width; j++) {
							for (int i = curPos.first + 1; i < height; i++) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//Check xiên xuống qua trái
					if (isCurFound == 0) {
						for (int j = curPos.second - 1; j >= 0; j--) {
							for (int i = curPos.first + 1; i < height; i++) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//check ngược lại
					if (isCurFound == 0) {
						for (int i = 0; i < curPos.first; i++)
							if (board.pBoard[i][curPos.second].pokemon != '0') {
								isCurFound = 1;
								curPos.first = i;
								break;
							}
					}
					break;

				case KEY_UP:
					Console::playSound(MOVE_SOUND);
					//Check lên trên
					if (isCurFound == 0) {
						for (int i = curPos.first - 1; i >= 0; i--)
							if (board.pBoard[i][curPos.second].pokemon != '0') {
								isCurFound = 1;
								curPos.first = i;
								break;
							}
					}

					//Check theo đường xiên lên qua phải
					if (isCurFound == 0) {
						for (int j = curPos.second + 1; j < width; j++) {
							for (int i = curPos.first - 1; i >= 0; i--) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//Check xiên lên qua trái
					if (isCurFound == 0) {
						for (int j = curPos.second - 1; j >= 0; j--) {
							for (int i = curPos.first - 1; i > 0; i--) {
								if (board.pBoard[i][j].pokemon != '0') {
									isCurFound = 1;
									curPos.first = i;
									curPos.second = j;
									break;
								}
							}
							if (isCurFound)
								break;
						}
					}

					//check ngược lại
					if (isCurFound == 0) {
						for (int i = height - 1; i > curPos.first; i--)
							if (board.pBoard[i][curPos.second].pokemon != '0') {
								isCurFound = 1;
								curPos.first = i;
								break;
							}
					}
					break;

				case KEY_ENTER:
					//Nếu ô đã chọn hay chưa chọn
					if (board.pBoard[curPos.first][curPos.second].isSelected == 0)
						board.pBoard[curPos.first][curPos.second].isSelected = 1;
					else
						board.pBoard[curPos.first][curPos.second].isSelected = 0;

					//Nếu chọn
					if (board.pBoard[curPos.first][curPos.second].isSelected == 1) {
						remainCell--;
						board.pBoard[curPos.first][curPos.second].drawCell(YELLOW);

						if (remainCell == 1) {
							selectedCell[0].first = curPos.first;
							selectedCell[0].second = curPos.second;
						}
						else if (remainCell == 0) {
							selectedCell[1].first = curPos.first;
							selectedCell[1].second = curPos.second;
						}

						if (remainCell == 0) {
							Sleep(250);
							check = gameplay.check2Cells(board.pBoard, height, width, board.pBoard[selectedCell[0].first][selectedCell[0].second], board.pBoard[selectedCell[1].first][selectedCell[1].second]);

							if (check.first != -2 || check.second != -2) { //check đúng
								gameplay.score += 2;
								Console::playSound(MOVE_SOUND);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].drawCell(GREEN);
								board.pBoard[selectedCell[1].first][selectedCell[1].second].drawCell(GREEN);
								gameplay.drawLine2Cells(board.pBoard, height, width, TOP, LEFT, board.pBoard[selectedCell[0].first][selectedCell[0].second], board.pBoard[selectedCell[1].first][selectedCell[1].second]);
								Console::setColor(WHITE, BLACK);
								Sleep(500);

								gameplay.eraseLine2Cells(board.pBoard, height, width, TOP, LEFT, board.pBoard[selectedCell[0].first][selectedCell[0].second], board.pBoard[selectedCell[1].first][selectedCell[1].second]);
								Console::setColor(WHITE, BLACK);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].deleteCell();
								board.pBoard[selectedCell[1].first][selectedCell[1].second].deleteCell();

								board.pBoard[selectedCell[0].first][selectedCell[0].second].pokemon = '0';
								board.pBoard[selectedCell[1].first][selectedCell[1].second].pokemon = '0';

								board.pBoard[selectedCell[0].first][selectedCell[0].second].isSelected = 0;
								board.pBoard[selectedCell[1].first][selectedCell[1].second].isSelected = 0;

								Board::displayBackground(board.pBoard, background, height, width);

								remainCell = 2;
								selectedCell[0].first = -2;
								selectedCell[0].second = -2;
								selectedCell[1].first = -2;
								selectedCell[1].second = -2;
							}
							else {
								Console::playSound(ERROR_SOUND);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].drawCell(RED);
								board.pBoard[selectedCell[1].first][selectedCell[1].second].drawCell(RED);
								Sleep(500);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].drawCell(WHITE);
								board.pBoard[selectedCell[1].first][selectedCell[1].second].drawCell(WHITE);

								board.pBoard[selectedCell[0].first][selectedCell[0].second].isSelected = 0;
								board.pBoard[selectedCell[1].first][selectedCell[1].second].isSelected = 0;

								remainCell = 2;
								selectedCell[0].first = -2;
								selectedCell[0].second = -2;
								selectedCell[1].first = -2;
								selectedCell[1].second = -2;
							}

							check = make_pair(-2, -2);
						}

					}

					//Nếu bỏ chọn
					else {
						remainCell++;

						board.pBoard[selectedCell[0].first][selectedCell[0].second].isSelected = 0;

						selectedCell[0].first = -2;
						selectedCell[0].second = -2;
					}
					break;
				case 'S':
					Console::playSound(MOVE_SOUND);
					gameplay.score -= 2;
					Console::gotoXY(70, 5);
					std::cout << "SHUFFLING...";
					Sleep(1000);
					Console::gotoXY(70, 5);
					std::cout << "            ";

					board.shuffle(height, width, board.pBoard);
					break;
				case 's':
					Console::playSound(MOVE_SOUND);
					gameplay.score -= 2;
					Console::gotoXY(70, 5);
					std::cout << "SHUFFLING...";
					Sleep(1000);
					Console::gotoXY(70, 5);
					std::cout << "            ";

					board.shuffle(height, width, board.pBoard);
					break;
				case 'A':
					Console::playSound(MOVE_SOUND);
					gameplay.score -= 2;
					moveSuggestion(height, width, board.pBoard);
					Sleep(500);
					break;
				case 'a':
					Console::playSound(MOVE_SOUND);
					gameplay.score -= 2;
					moveSuggestion(height, width, board.pBoard);
					Sleep(500);
					break;
				case 'I':
					end = clock();
					playTime += (double)(end - start) / CLOCKS_PER_SEC;

					Console::playSound(MENU_SOUND);
					Console::clearConsole();
					Console::setColor(WHITE, BLUE);
					Console::gotoXY(57, 0);
					std::cout << "Play time up to now: " << playTime << "s...";
					Console::setColor(WHITE, BLACK);

					Menu::helpScreen();

					Board::displayBackground(board.pBoard, background, height, width);
					start = clock();
					break;
				case 'i':
					end = clock();
					playTime += (double)(end - start) / CLOCKS_PER_SEC;

					Console::playSound(MENU_SOUND);
					Console::clearConsole();
					Console::setColor(WHITE, BLUE);
					Console::gotoXY(57, 0);
					std::cout << "Play time up to now: " << playTime << "s...";
					Console::setColor(WHITE, BLACK);

					Menu::helpScreen();

					Board::displayBackground(board.pBoard, background, height, width);
					start = clock();
					break;
				default:
					true_while_flag = 1;
					break;
				}
				if (true_while_flag == 0)
					break;
			}
		}
		else {
			Sleep(500);
		}

		if (gameplay.validPair == 0 && gameplay.remainingCell == 0) {
			end = clock();
			playTime += (double)(end - start) / CLOCKS_PER_SEC;

			account.time = int(playTime);
			account.isFinished = 1;
			account.score = gameplay.score;
			account.mode = mode;

			std::system("cls");
			Menu::winScreen(account);
			isPlaying = 0;
		}
		else if (gameplay.validPair == 0 && gameplay.remainingCell != 0) {
			Console::gotoXY(70, 5);
			std::cout << "OUT OF MOVE! SHUFFLING...";
			Sleep(1000);
			Console::gotoXY(70, 5);
			std::cout << "                         ";
			board.shuffle(height, width, board.pBoard);
		}
	}

	const char* Username = account.UserName.c_str();

	ofstream ofs("Leaderboard\\leaderboard.bin", ios::out | ios::app | ios::binary);

	if (ofs) {
		ofs.write(reinterpret_cast<char*> (&account.Num), sizeof(int));
		ofs.write(Username, 20);
		ofs.write(reinterpret_cast<char*> (&account.mode), sizeof(int));
		ofs.write(reinterpret_cast<char*> (&account.score), sizeof(int));
		ofs.write(reinterpret_cast<char*> (&account.time), sizeof(int));
		ofs.close();
	}
	else {
		exit(1);
	}

	Board::clearBackground(background, height);
	board.clearBoard(board.pBoard);
}

void moveSuggestion(int height, int width, Cell** pBoard) {
	GamePlay gameplay;
	pair<int, int> check(-2, -2);

	for (int i = 0; i < height * width; i++) {
		if (pBoard[i / width][i % width].pokemon != '0') {
			for (int j = i + 1; j < height * width; j++) {
				if (pBoard[j / width][j % width].pokemon == pBoard[i / width][i % width].pokemon) {
					check = gameplay.check2Cells(pBoard, height, width, pBoard[j / width][j % width], pBoard[i / width][i % width]);

					if (check.first != -2 || check.second != -2) {
						pBoard[j / width][j % width].drawCell(PURPLE);
						pBoard[i / width][i % width].drawCell(PURPLE);
						return;
					}

					check = make_pair( - 2, -2);
				}
			}
		}
	}
}