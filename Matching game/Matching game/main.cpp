#include "console.h"
#include "menu.h"
#include "board.h"
#include "gameplay.h"
#include "gamemode.h"
#include "login.h"

int main() {
	Console::setupConsole();
	Menu::printAnimation();

	Account account;
	LoginScreen::loginScreen(account);

	int status = 0;
	int mode = 0;
	int exit = 0;

	status = Menu::mainMenu(account);
	while (status != 3 || exit != 1) {
		if (status == 0) {
			mode = Menu::modeSelectMenu(account);
			if (mode == 0)
				GameMode::createNormalGame(account);
			else if (mode == 1) {
				GameMode::createHardGame_2DPointerArray(account);
				//GameMode::createHardGame_LinkedList(account);
			}
			else if (mode == 2) {
				int custom = Menu::customScreen(account);	//custom = 2, 3, 4, 5
				if (custom != 5)
					GameMode::createCustomGame(account, custom + 1, custom + 2, custom);
			}
			else if (mode == 3)
				status = Menu::mainMenu(account);
		}

		else if (status == 1) {
			Console::clearConsole();
			Menu::helpScreen();
			status = Menu::mainMenu(account);
		}
			
		else if (status == 2) {
			Menu::leaderBoard();
			status = Menu::mainMenu(account);
		}

		else if (status == 3) {
			exit = Menu::exitScreen();
			if (exit == 0)
				status = Menu::mainMenu(account);
		}
	}

	cin.get();
}