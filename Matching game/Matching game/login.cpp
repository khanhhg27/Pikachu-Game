#include "login.h"

void LoginScreen::loginScreen(Account& account) {
	int choice[3] = { 0,0,0 };
	int key = 0;
	int curChoice = 0;
	bool EXIT = 0;
	bool isLogin = 0;

	while (true) {
		printLogo();

		printRectangle(42, 20, 15, 2);
		printRectangle(62, 20, 15, 2);
		printRectangle(82, 20, 21, 2);


		choice[curChoice] = 1;

		if (choice[0]) {
			Console::gotoXY(45, 21);
			Console::setColor(LIGHT_RED, BLACK);
			std::cout << "  LOG IN  ";
		}
		else {
			Console::gotoXY(45, 21);
			Console::setColor(WHITE, BLACK);
			std::cout << "  LOG IN  ";
		}
		if (choice[1]) {
			Console::gotoXY(65, 21);
			Console::setColor(LIGHT_RED, BLACK);
			std::cout << "  SIGN UP  ";
		}
		else {
			Console::gotoXY(65, 21);
			Console::setColor(WHITE, BLACK);
			std::cout << "  SIGN UP  ";
		}

		if (choice[2]) {
			Console::gotoXY(85, 21);
			Console::setColor(LIGHT_RED, BLACK);
			std::cout << "  PLAY AS GUEST  ";
		}
		else {
			Console::gotoXY(85, 21);
			Console::setColor(WHITE, BLACK);
			std::cout << "  PLAY AS GUEST  ";
		}

		Console::setColor(WHITE, BLACK);

		while (true) {
			int flag = 0;
			key = _getch();

			switch (key) {
			case KEY_ENTER:
				std::system("cls");
				printLogo();

				if (curChoice == 0) {
					isLogin = doLogin(account);
					if (isLogin) {
						printAccountName(account);
						return;
					}
					else
						break;
				}
				else if (curChoice == 1) {
					doSignup();
					break;
				}
				else {
					account.UserName = "Guest account";
					account.Num = 0;
					printAccountName(account);
					return;
				}

			case KEY_RIGHT:
				Console::playSound(MENU_SOUND);
				choice[curChoice] = 0;
				if (curChoice < 2) curChoice++;
				else curChoice = 0;
				break;

			case KEY_LEFT:
				Console::playSound(MENU_SOUND);
				choice[curChoice] = 0;
				if (curChoice > 0) curChoice--;
				else curChoice = 0;
				break;

			default:
				flag = 1;
				break;
			}

			if (flag == 0)
				break;

		}
	}
}

bool LoginScreen::doLogin(Account& login) {
	string line = "";

	while (true) { 
		bool true_while_flag = 0;
		bool checkUserName = 0;
		bool checkPassWord = 0;

		login.UserName.clear();
		login.Password.clear();

		//Nhập vào Username và password
		Console::setColor(WHITE, BLACK);
		Console::gotoXY(25, 18);
		std::cout << "Please enter your account infomation below.";

		Console::setColor(WHITE, BLACK);
		Console::gotoXY(30, 20);
		std::cout << "Enter user name: ";

		Console::showCursor(true);
		Console::gotoXY(48, 20);
		std::getline(std::cin, login.UserName);
		Console::showCursor(false);

		if (login.UserName == "Please Come Back!") {
			system("cls");
			return 0;
		}

		Console::gotoXY(30, 22);
		std::cout << "Enter your password: ";

		Console::showCursor(true);
		Console::gotoXY(52, 22);
		std::getline(std::cin, login.Password);
		Console::showCursor(false);

		ifstream ifs("Account\\account.txt");

		if (!ifs.is_open()) {
			exit(1);
		}	

		if (login.UserName != "" && login.Password != "") {
			while (!ifs.eof()) {
				line.clear();
				string token = "";

				std::getline(ifs, line);	//line = "1/username/password"
				if (line == "")
					break;
				stringstream ss(line);
				getline(ss, token, '/');	//token = 1
				login.Num = std::stoi(token);

				getline(ss, token, '/');	//token = "username"
				if (token == login.UserName)
					checkUserName = 1;
				getline(ss, token);			//token = "password"
				if (token == login.Password)
					checkPassWord = 1;

				if (checkUserName && checkPassWord) {
					Console::setColor(WHITE, GREEN);
					Console::gotoXY(32, 26);
					std::cout << "Login Successfully!";
					Console::setColor(WHITE, BLACK);
					ifs.close();
					Sleep(1000);
					std::system("cls");

					return 1;
				}
				else {
					checkUserName = 0;
					checkPassWord = 0;
				}
			}
		}

		//Fail to login
		Console::setColor(WHITE, RED);
		Console::gotoXY(32, 26);
		std::cout << "Wrong Login Info!!!";
		Console::setColor(WHITE, BLACK);

		//To comeback
		Console::setColor(WHITE, BLUE);
		Console::gotoXY(32, 28);
		std::cout << "Don't have account? Write 'Please Come Back!' as username to return to make your own account :)))";
		Console::setColor(WHITE, BLACK);

		//Xóa màn hình
		for (int i = 0; i < login.UserName.size(); i++) {
			Console::gotoXY(48 + i, 20);
			std::cout << " ";
		}
		for (int i = 0; i < login.Password.size(); i++) {
			Console::gotoXY(52 + i, 22);
			std::cout << " ";
		}

		true_while_flag = 1;
		ifs.close();

		if (true_while_flag == 0) {
			break;
		}
	}
}

void LoginScreen::doSignup() {
	// If user choose SIGN UP

	Account p;
	string re_Password;
	while (true) {	//Đăng ký tài khoản
		bool true_while_flag = 0;
		int accountNumber = 0;

		Console::setColor(WHITE, BLACK);
		Console::gotoXY(25, 17);
		std::cout << "Please enter all information bellow, under 15 characters !";
		Console::gotoXY(25, 18);
		std::cout << "Your username will be used as your account name.";

		Console::setColor(WHITE, BLACK);
		Console::gotoXY(30, 20);
		std::cout << "Enter user name: ";

		Console::showCursor(true);
		Console::gotoXY(48, 20);
		std::getline(std::cin, p.UserName);
		Console::showCursor(false);

		if (p.UserName.size() > 15) {
			for (int i = 0; i < p.UserName.size(); i++) {
				Console::gotoXY(48 + i, 20);
				std::cout << " ";
			}

			Console::gotoXY(32, 26);
			Console::setColor(WHITE, RED);
			std::cout << "More than 15 chars!";
			Console::setColor(WHITE, BLACK);

			p.UserName.clear();
			true_while_flag = 1;
		}
		else if (p.UserName == "") {
			for (int i = 0; i < p.UserName.size(); i++) {
				Console::gotoXY(48 + i, 20);
				std::cout << " ";
			}

			Console::gotoXY(32, 26);
			Console::setColor(WHITE, RED);
			std::cout << "Enter your username";
			Console::setColor(WHITE, BLACK);

			p.UserName.clear();
			true_while_flag = 1;
		}

		if (true_while_flag == 0) {
			ifstream ifs("Account\\account.txt");
			string temp, token;
			bool checkUsername = 0;

			while (!ifs.eof()) {
				getline(ifs, temp);			//temp = 1/username/password
				stringstream ss(temp);		//ss = 1/username/password
				getline(ss, token, '/');	//token = 1
				getline(ss, token, '/');	//token = username
				if (token == p.UserName)
					checkUsername = 1;
				getline(ss, token, '/');	//token = password
				accountNumber++;
			}
			ifs.close();

			if (checkUsername == 1) {
				for (int i = 0; i < p.UserName.size(); i++) {
					Console::gotoXY(48 + i, 20);
					std::cout << " ";
				}

				Console::gotoXY(32, 26);
				Console::setColor(WHITE, RED);
				std::cout << "Username existed!!!";
				Console::setColor(WHITE, BLACK);

				p.UserName.clear();
				true_while_flag = 1;
			}
		}

		if (true_while_flag == 0) {
			do {
				re_Password.clear();
				p.Password.clear();

				Console::gotoXY(30, 22);
				std::cout << "Create new password: ";

				Console::showCursor(true);
				Console::gotoXY(52, 22);
				std::getline(std::cin, p.Password);
				Console::showCursor(false);

				if (p.Password.size() > 15) {
					for (int i = 0; i < p.Password.size(); i++) {
						Console::gotoXY(52 + i, 22);
						std::cout << " ";
					}

					for (int i = 0; i < p.UserName.size(); i++) {
						Console::gotoXY(48 + i, 20);
						std::cout << " ";
					}

					Console::gotoXY(32, 26);
					Console::setColor(WHITE, RED);
					std::cout << "More than 15 chars!";
					Console::setColor(WHITE, BLACK);

					p.Password.clear();
					p.UserName.clear();
					true_while_flag = 1;
					break;
				}

				Console::gotoXY(30, 24);
				std::cout << "Repeat password: ";

				Console::showCursor(true);
				Console::gotoXY(48, 24);
				std::getline(cin, re_Password);
				Console::showCursor(false);

				if (re_Password.size() > 15) {
					for (int i = 0; i < re_Password.size(); i++) {
						Console::gotoXY(48 + i, 24);
						std::cout << " ";
					}

					for (int i = 0; i < p.UserName.size(); i++) {
						Console::gotoXY(48 + i, 20);
						std::cout << " ";
					}

					for (int i = 0; i < p.Password.size(); i++) {
						Console::gotoXY(52 + i, 22);
						std::cout << " ";
					}

					Console::gotoXY(32, 26);
					Console::setColor(WHITE, RED);
					std::cout << "More than 15 chars!";
					Console::setColor(WHITE, BLACK);

					re_Password.clear();
					p.Password.clear();
					p.UserName.clear();
					true_while_flag = 1;
					break;
				}

				if (re_Password != p.Password) {
					for (int i = 1; i <= p.Password.size(); i++) {
						Console::gotoXY(51 + i, 22);
						std::cout << " ";
					}
					for (int i = 1; i <= re_Password.size(); i++) {
						Console::gotoXY(47 + i, 24);
						std::cout << " ";
					}

					Console::setColor(WHITE, RED);
					Console::gotoXY(32, 26);
					std::cout << "Invalid password!!!";
					Console::setColor(WHITE, BLACK);
				}
				else {
					ofstream ofs("Account\\account.txt", ios::app);
					ofs << accountNumber << "/";
					ofs << p.UserName << "/";
					ofs << p.Password;
					ofs << endl;
					ofs.close();
				} 

			} while (re_Password != p.Password);
		}
		if (true_while_flag == 0)
			break;
	}



	Console::setColor(WHITE, GREEN);
	Console::gotoXY(32, 26);
	std::cout << "Successful Created!";
	Console::setColor(WHITE, BLACK);
	Sleep(1000);
	std::system("cls");

	return;
}

void LoginScreen::printAccountName(Account account) {
	Console::gotoXY(0, 0);
	std::cout << "Account: " << account.UserName;
}


void printLogo() {
	Console::gotoXY(0, 1);
	cout << R"(
                                       _______   __     __   ___       __       ______    __    __   ____  ____  
                                      |   __ "\ |" \   |/"| /  ")     /""\     /" _  "\  /" |  | "\ ("  _||_ " | 
                                      (. |__) :)||  |  (: |/   /     /    \   (: ( \___)(:  (__)  :)|   (  ) : | 
                                      |:  ____/ |:  |  |    __/     /' /\  \   \/ \      \/      \/ (:  |  | . ) 
                                      (|  /     |.  |  (// _  \    //  __'  \  //  \ _   //  __  \\  \\ \__/ //  
                                     /|__/ \    /\  |\ |: | \  \  /   /  \\  \(:   _) \ (:  (  )  :) /\\ __ //\  
                                    (_______)  (__\_|_)(__|  \__)(___/    \___)\_______) \__|  |__/ (__________) 
                                                                             
                                                                             
    )";
}

void printDoubleRectangle(int left, int top, int width, int height) {
	Console::gotoXY(left, top);
	putchar(201);
	for (int i = 0; i < width; i++)
		putchar(205);
	putchar(187);

	int i = 0;
	for (; i < height; i++)
	{
		Console::gotoXY(left, top + i + 1);
		putchar(186);
		Console::gotoXY(left + width + 1, top + i + 1);
		putchar(186);
	}

	Console::gotoXY(left, top + i);
	putchar(200);
	for (i = 0; i < width; i++)
		putchar(205);
	putchar(188);
}

void printRectangle(int left, int top, int width, int height) {
	Console::gotoXY(left, top);
	putchar(218);
	for (int i = 0; i < width; i++)
		putchar(196);
	putchar(191);

	int i = 0;
	for (; i < height; i++)
	{
		Console::gotoXY(left, top + i + 1);
		putchar(179);
		Console::gotoXY(left + width + 1, top + i + 1);
		putchar(179);
	}

	Console::gotoXY(left, top + i);
	putchar(192);
	for (i = 0; i < width; i++)
		putchar(196);
	putchar(217);
}