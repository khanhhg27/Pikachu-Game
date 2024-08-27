#include "menu.h"

using namespace std;

int Menu::mainMenu(Account account) {
    Console::playSound(MENU_SOUND);
    Console::setColor(WHITE, BLACK);

    drawFaceRightPikachu();
    drawFaceLeftPikachu();
    printLogo();
    LoginScreen::printAccountName(account);

    printDoubleRectangle(64, 13, 15, 13);
    printRectangle(65, 14, 13, 2);
    printRectangle(65, 17, 13, 2);
    printRectangle(65, 20, 13, 2);
    printRectangle(65, 23, 13, 2);

    int choice[4] = { 0,0,0,0 };
    int key = 0;
    int curChoice = 0;
    int EXIT = 0;

    while (true) {
        choice[curChoice] = 1;

        if (choice[0]) {
            Console::gotoXY(67, 15);
            Console::setColor(LIGHT_RED, BLACK);
            std::cout << " NEW GAME ";
        }
        else {
            Console::gotoXY(67, 15);
            Console::setColor(WHITE, BLACK);
            std::cout << " NEW GAME ";
        }
        if (choice[1]) {
            Console::gotoXY(69, 18);
            Console::setColor(LIGHT_RED, BLACK);
            std::cout << " HELP ";
        }
        else {
            Console::gotoXY(69, 18);
            Console::setColor(WHITE, BLACK);
            std::cout << " HELP ";
        }

        if (choice[2]) {
            Console::gotoXY(66, 21);
            Console::setColor(LIGHT_RED, BLACK);
            std::cout << " LEADERBOARD ";
        }
        else {
            Console::gotoXY(66, 21);
            Console::setColor(WHITE, BLACK);
            std::cout << " LEADERBOARD ";
        }

        if (choice[3]) {
            Console::gotoXY(69, 24);
            Console::setColor(LIGHT_RED, BLACK);
            std::cout << " EXIT ";
        }
        else {
            Console::gotoXY(69, 24);
            Console::setColor(WHITE, BLACK);
            std::cout << " EXIT ";
        }

        Console::setColor(WHITE, BLACK);

       while (true) {
            int flag = 0;
            key = _getch();
            switch (key) {
            case KEY_ENTER:
                std::system("cls");
                return curChoice;
            case KEY_UP:
                Console::playSound(MENU_SOUND);
                choice[curChoice] = 0;
                if (curChoice > 0) curChoice--;
                else curChoice = 3;
                break;
            case KEY_DOWN:
                Console::playSound(MENU_SOUND);
                choice[curChoice] = 0;
                if (curChoice < 3) curChoice++;
                else curChoice = 0;
                break;
            case KEY_ESC:
                Console::playSound(MENU_SOUND);
                std::system("cls");
                EXIT = exitScreen();
                if (EXIT == 0) {
                    printLogo();
                    drawFaceRightPikachu();
                    drawFaceLeftPikachu();
                    LoginScreen::printAccountName(account);

                    printDoubleRectangle(64, 13, 15, 13);
                    printRectangle(65, 14, 13, 2);
                    printRectangle(65, 17, 13, 2);
                    printRectangle(65, 20, 13, 2);
                    printRectangle(65, 23, 13, 2);

                    flag = 0;
                    break;
                }
                else 
                    exit(0);
            default:
                flag = 1;
                break;
            }

            if (flag == 0)
                break;
        }
    }
}

int Menu::modeSelectMenu(Account account) {
    Console::playSound(MENU_SOUND);
    Console::setColor(WHITE, BLACK);

    drawFaceRightPikachu();
    drawFaceLeftPikachu();
    printLogo();
    LoginScreen::printAccountName(account);

    printDoubleRectangle(65, 13, 14, 13);
    printRectangle(67, 14, 10, 2);
    printRectangle(67, 17, 10, 2);
    printRectangle(67, 20, 10, 2);
    printRectangle(67, 23, 10, 2);

    int choice[4] = { 0,0,0,0 };
    int key = 0;
    int curChoice = 0;
    int EXIT = 0;


    while (true) {
        choice[curChoice] = 1;

        if (choice[0]) {
            Console::gotoXY(69, 15);
            Console::setColor(LIGHT_RED, BLACK);
            std::cout << " NORMAL ";
        }
        else {
            Console::gotoXY(69, 15);
            Console::setColor(WHITE, BLACK);
            std::cout << " NORMAL ";
        }
        if (choice[1]) {
            Console::gotoXY(70, 18);
            Console::setColor(LIGHT_RED, BLACK);
            std::cout << " HARD ";
        }
        else {
            Console::gotoXY(70, 18);
            Console::setColor(WHITE, BLACK);
            std::cout << " HARD ";
        }

        if (choice[2]) {
            Console::gotoXY(69, 21);
            Console::setColor(LIGHT_RED, BLACK);
            std::cout << " CUSTOM ";
        }
        else {
            Console::gotoXY(69, 21);
            Console::setColor(WHITE, BLACK);
            std::cout << " CUSTOM ";
        }

        if (choice[3]) {
            Console::gotoXY(70, 24);
            Console::setColor(LIGHT_RED, BLACK);
            std::cout << " BACK ";
        }
        else {
            Console::gotoXY(70, 24);
            Console::setColor(WHITE, BLACK);
            std::cout << " BACK ";
        }

        Console::setColor(WHITE, BLACK);

        while (true) {
            int flag = 0;

            key = _getch();
            switch (key) {
            case KEY_ENTER:
                std::system("cls");
                return curChoice;
            case KEY_UP:
                Console::playSound(MENU_SOUND);
                choice[curChoice] = 0;
                if (curChoice > 0) curChoice--;
                else curChoice = 3;
                break;
            case KEY_DOWN:
                Console::playSound(MENU_SOUND);
                choice[curChoice] = 0;
                if (curChoice < 3) curChoice++;
                else curChoice = 0;
                break;
            case KEY_ESC:
                Console::playSound(MENU_SOUND);
                std::system("cls");
                EXIT = exitScreen();
                if (EXIT == 0) {
                    printLogo();
                    drawFaceRightPikachu();
                    drawFaceLeftPikachu();
                    LoginScreen::printAccountName(account);

                    printDoubleRectangle(64, 13, 15, 13);
                    printRectangle(65, 14, 13, 2);
                    printRectangle(65, 17, 13, 2);
                    printRectangle(65, 20, 13, 2);
                    printRectangle(65, 23, 13, 2);

                    flag = 0;
                    break;
                }
                else
                    exit(0);
            default:
                flag = 1;
                break;
            }

            if (flag == 0)
                break;
        }
    }
}

void Menu::printRectangle(int left, int top, int width, int height)
{
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

void Menu::printDoubleRectangle(int left, int top, int width, int height)
{
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

void Menu::printAnimation()
{
    srand((unsigned int)time(NULL));
    Console::playSound(WIN_SOUND);
    
    printLogo();
    printPikachu();

    int colorList[] = { 1, 2, 4, 5, 6 };
    int loop = 10;

    int symbol[] = { 4, 15 };
    bool turn = 0;

    while (loop--) {
        Console::setColor(WHITE, colorList[rand() % 5]);

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                Console::gotoXY(i * 20 + 3, j * 10 + 1);
                std::putchar(symbol[turn]);
            }
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 2; j++) {
                Console::gotoXY(i * 20 + 13, j * 10 + 16);
                std::putchar(symbol[turn]);
            }
        }

        for (int i = 6; i < 8; i++) {
            for (int j = 0; j < 2; j++) {
                Console::gotoXY(i * 20 + 3, j * 10 + 1);
                std::putchar(symbol[turn]);
            }
        }

        Console::gotoXY(13, 6);
        std::putchar(symbol[turn]);
        Console::gotoXY(113, 6);
        std::putchar(symbol[turn]);
        Console::gotoXY(133, 6);
        std::putchar(symbol[turn]);
        Console::gotoXY(123, 31);
        std::putchar(symbol[turn]);
        Console::gotoXY(143, 31);
        std::putchar(symbol[turn]);

        turn = !turn;
        Sleep(300);
    }
  
    Console::setColor(WHITE, BLACK);
    std::system("cls");
}

void Menu::printLogo() {
    Console::gotoXY(0, 1);
    std::cout << R"(
                                       _______   __     __   ___       __       ______    __    __   ____  ____  
                                      |   __ "\ |" \   |/"| /  ")     /""\     /" _  "\  /" |  | "\ ("  _||_ " | 
                                      (. |__) :)||  |  (: |/   /     /    \   (: ( \___)(:  (__)  :)|   (  ) : | 
                                      |:  ____/ |:  |  |    __/     /' /\  \   \/ \      \/      \/ (:  |  | . ) 
                                      (|  /     |.  |  (// _  \    //  __'  \  //  \ _   //  __  \\  \\ \__/ //  
                                     /|__/ \    /\  |\ |: | \  \  /   /  \\  \(:   _) \ (:  (  )  :) /\\ __ //\  
                                    (_______)  (__\_|_)(__|  \__)(___/    \___)\_______) \__|  |__/ (__________) 
                                                                             
                                                                             
    )";
}

void Menu::printPikachu() {
    Console::gotoXY(105, 11);
    std::cout << "-%#=.                            .::     ";
    Console::gotoXY(105, 12);
    std::cout << " =@%---:                    .--=%@@-     ";
    Console::gotoXY(105, 13);
    std::cout << "  :%+----:                :==---@%:      ";
    Console::gotoXY(105, 14);
    std::cout << "    -------:    ....    .------+=    ... ";
    Console::gotoXY(105, 15);
    std::cout << "      :-----::---------------:. .::----- ";
    Console::gotoXY(105, 16);
    std::cout << "         :=---------------::::---------: ";
    Console::gotoXY(105, 17);
    std::cout << "         :----------------=-----------=  ";
    Console::gotoXY(105, 18);
    std::cout << "         :-+#-+------==+#-=-----------:  ";
    Console::gotoXY(105, 19);
    std::cout << "         --+%%+---=---#%#---------::..   ";
    Console::gotoXY(105, 20);
    std::cout << "        .##*------------=+*+---.         ";
    Console::gotoXY(105, 21);
    std::cout << "         *##+-----------###*----.        ";
    Console::gotoXY(105, 22);
    std::cout << "          ++------------=*= ------       ";
    Console::gotoXY(105, 23);
    std::cout << "          --------------------:..        ";
    Console::gotoXY(105, 24);
    std::cout << "         ------------------+#+           ";
    Console::gotoXY(105, 25);
    std::cout << "        --------=---=-------:            ";
    Console::gotoXY(105, 26);
    std::cout << "       ----------=-=---------.           ";
    Console::gotoXY(105, 27);
    std::cout << "    -=-=---------=-=-----------=         ";
    Console::gotoXY(105, 28);
    std::cout << "     -==--=------=-=--------===.         ";
    Console::gotoXY(105, 29);
    std::cout << "      .======---===+---======:           ";
}

int Menu::exitScreen() {
    Console::setColor(WHITE, BLACK);
    printLogo();

    drawFaceRightPikachu();
    drawFaceLeftPikachu();
 
    printDoubleRectangle(59, 14, 20, 2);
    printRectangle(62, 17, 4, 2);
    printRectangle(70, 17, 5, 2);
    Console::gotoXY(60, 15);
    std::cout << "Do you want to quit?";

    int choice[2] = {0,0};
    int key = 0;
    int curChoice = 0;

    while (true) {
        choice[curChoice] = 1;

        if (choice[0]) {
            Console::gotoXY(63, 18);
            Console::setColor(LIGHT_RED, BLACK);
            std::cout << " NO ";
        }
        else {
            Console::gotoXY(63, 18);
            Console::setColor(WHITE, BLACK);
            std::cout << " NO ";
        }
        if (choice[1]) {
            Console::gotoXY(71, 18);
            Console::setColor(LIGHT_RED, BLACK);
            std::cout << " YES ";
        }
        else {
            Console::gotoXY(71, 18);
            Console::setColor(WHITE, BLACK);
            std::cout << " YES ";
        }
        Console::setColor(WHITE, BLACK);

        while (true) {
            int flag = 0;

            key = _getch();
            switch (key) {
            case KEY_ENTER:
                std::system("cls");
                return curChoice;
            case KEY_RIGHT:
                Console::playSound(MENU_SOUND);
                choice[curChoice] = 0;
                if (curChoice == 0) curChoice++;
                else curChoice--;
                break;
            case KEY_LEFT:
                Console::playSound(MENU_SOUND);
                choice[curChoice] = 0;
                if (curChoice == 0) curChoice++;
                else curChoice--;
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

int Menu::customScreen(Account account) {
    printLogo();

    LoginScreen::printAccountName(account);
    drawFaceRightPikachu();
    drawFaceLeftPikachu();

    printDoubleRectangle(51, 14, 45, 2);
    printRectangle(55, 17, 7, 2);
    printRectangle(65, 17, 7, 2);
    printRectangle(75, 17, 7, 2);
    printRectangle(85, 17, 6, 2);

    Console::gotoXY(52, 15);
    std::cout << "Choose the board size that you want to play!!";

    int choice[4] = { 0,0,0,0 };
    int key = 0;
    int curChoice = 0;
    int EXIT = 0;

    while (true) {
        choice[curChoice] = 1;

        if (choice[0]) {
            Console::gotoXY(56, 18);
            Console::setColor(LIGHT_RED, BLACK);
            std::cout << " 3 x 4 ";
        }
        else {
            Console::gotoXY(56, 18);
            Console::setColor(WHITE, BLACK);
            std::cout << " 3 x 4 ";
        }
        if (choice[1]) {
            Console::gotoXY(66, 18);
            Console::setColor(LIGHT_RED, BLACK);
            std::cout << " 4 x 5 ";
        }
        else {
            Console::gotoXY(66, 18);
            Console::setColor(WHITE, BLACK);
            std::cout << " 4 x 5 ";
        }
        if (choice[2]) {
            Console::gotoXY(76, 18);
            Console::setColor(LIGHT_RED, BLACK);
            std::cout << " 5 x 6 ";
        }
        else {
            Console::gotoXY(76, 18);
            Console::setColor(WHITE, BLACK);
            std::cout << " 5 x 6 ";
        }
        if (choice[3]) {
            Console::gotoXY(86, 18);
            Console::setColor(LIGHT_RED, BLACK);
            std::cout << " BACK ";
        }
        else {
            Console::gotoXY(86, 18);
            Console::setColor(WHITE, BLACK);
            std::cout << " BACK ";
        }
        Console::setColor(WHITE, BLACK);

        while (true) {
            int flag = 0;
            key = _getch();

            switch (key) {
            case KEY_ESC:
                Console::playSound(MENU_SOUND);
                std::system("cls");
                EXIT = exitScreen();
                if (EXIT == 0) {
                    printLogo();

                    LoginScreen::printAccountName(account);
                    drawFaceRightPikachu();
                    drawFaceLeftPikachu();

                    printDoubleRectangle(51, 14, 45, 2);
                    printRectangle(60, 17, 7, 2);
                    printRectangle(70, 17, 7, 2);
                    printRectangle(80, 17, 7, 2);

                    Console::gotoXY(52, 15);
                    std::cout << "Choose the board size that you want to play!!";

                    flag = 0;
                    break;
                }
                else
                    exit(0);

            case KEY_ENTER:
                std::system("cls");
                return (curChoice + 2);
            case KEY_RIGHT:
                Console::playSound(MENU_SOUND);
                choice[curChoice] = 0;
                if (curChoice < 3) curChoice++;
                else curChoice = 0;
                break;
            case KEY_LEFT:
                Console::playSound(MENU_SOUND);
                choice[curChoice] = 0;
                if (curChoice > 0) curChoice--;
                else curChoice = 3;
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

void Menu::leaderBoard() {
    //vẽ console
    Console::setColor(WHITE, LIGHT_RED);
    std::cout << R"(
                                    .__                     .___          ___.                          .___
                                    |  |   ____ _____     __| _/__________\_ |__   _________ _______  __| _/
                                    |  | _/ __ \\__  \   / __ |/ __ \_  __ \ __ \ /  _ \__  \\_  __ \/ __ | 
                                    |  |_\  ___/ / __ \_/ /_/ \  ___/|  | \/ \_\ (  <_> ) __ \|  | \/ /_/ | 
                                    |____/\___  >____  /\____ |\___  >__|  |___  /\____(____  /__|  \____ | 
                                              \/     \/      \/    \/          \/           \/           \/ 
                                            
	)";
    Console::setColor(WHITE, BLACK);
    printRectangle(5, 8, 135, 21);

    for (int i = 6; i < 141; i++)
    {
        Console::gotoXY(i, 10);
        putchar(196);
    }

    Console::setColor(WHITE, BLUE);

    Console::gotoXY(8, 9);
    std::cout << "STT";

    Console::gotoXY(36, 9);
    std::cout << "Name";

    Console::gotoXY(77, 9);
    std::cout << "Mode";

    Console::gotoXY(104, 9);
    std::cout << "Score";

    Console::gotoXY(128, 9);
    std::cout << "Time";

    Console::setColor(WHITE, BLACK);

    for (int i = 1; i < 21; i++)
    {
        Console::gotoXY(13, 8 + i);
        putchar(179);
    }
    for (int i = 1; i < 21; i++)
    {
        Console::gotoXY(63, 8 + i);
        putchar(179);
    }

    for (int i = 1; i < 21; i++)
    {
        Console::gotoXY(94, 8 + i);
        putchar(179);
    }
    for (int i = 1; i < 21; i++)
    {
        Console::gotoXY(118, 8 + i);
        putchar(179);
    }

    fstream fs("Leaderboard\\leaderboard.bin", ios::in | ios::binary);

    Account listAccountRecord[50];

    if (fs) {
        char Username[20];
        int numOfitems = 0;
        fs.seekg(0L, ios::end);

        numOfitems = int(fs.tellg()) / 36;

        fs.seekg(0L, ios::beg);

        for (int i = 0; i < numOfitems; i++) {
            fs.read(reinterpret_cast<char*> (&listAccountRecord[i].Num), sizeof(int));
            fs.read(Username, sizeof(Username));
            fs.read(reinterpret_cast<char*> (&listAccountRecord[i].mode), sizeof(int));
            fs.read(reinterpret_cast<char*> (&listAccountRecord[i].score), sizeof(int));
            fs.read(reinterpret_cast<char*> (&listAccountRecord[i].time), sizeof(int));

            listAccountRecord[i].UserName = Username;
        }
        
        //Sort giảm dần theo điểm số
        for (int i = 0; i < numOfitems - 1; i++)
            for (int j = i + 1; j < numOfitems; j++)
                if (listAccountRecord[i].score < listAccountRecord[j].score)
                    swap(listAccountRecord[i], listAccountRecord[j]);

        //Sort tăng dần theo thời gian
        for (int i = 0; i < numOfitems - 1; i++)
            for (int j = i + 1; j < numOfitems; j++)
                if (listAccountRecord[i].time > listAccountRecord[j].time && listAccountRecord[i].score == listAccountRecord[j].score)
                    swap(listAccountRecord[i], listAccountRecord[j]);

        //display 18 best record
        for (int i = 0; i < 18; i++) {
            //Cột stt
            Console::gotoXY(9, 11 + i);
            std::cout << i + 1;

            //Cột name
            Console::gotoXY(33, 11 + i);
            std::cout << listAccountRecord[i].UserName;

            //Cột mode
            Console::gotoXY(75, 11 + i);
            if (listAccountRecord[i].mode == 0)
                std::cout << "NORMAL";
            else if (listAccountRecord[i].mode == 1)
                std::cout << "HARD";
            else if (listAccountRecord[i].mode == 2)
                std::cout << "CUSTOM";
            else if (listAccountRecord[i].mode == 3)
                std::cout << "CUSTOM";
            else if (listAccountRecord[i].mode == 4)
                std::cout << "CUSTOM";
            //Cột score
            Console::gotoXY(106, 11 + i);
            std::cout << listAccountRecord[i].score;

            //Cột time
            Console::gotoXY(128, 11 + i);
            std::cout << listAccountRecord[i].time << "s";
        }
        
        fs.close();
    }  
    else {
        exit(1);
    }

   
    

    printRectangle(50, 32, 40, 2);
    Console::gotoXY(51, 33);
    std::cout << "PRESS ANY BUTTON TO RETURN TO MAIN MENU!";

    int key = _getch();
    std::system("cls");
    return;
}

void Menu::helpScreen() {
    Console::setColor(WHITE, BLACK);

    int left = 10, top = 2, width = 125, height = 28;
    int line1 = 6, line2 = 19;
    int line3 = 25, line4 = 15, line5 = 20;

    Menu::printRectangle(left, top, width, height);
    Console::gotoXY(left + 1, line1 + 2);
    for (int i = 0; i < width; i++) {
        putchar(196);
    }
    Console::gotoXY(left + 1, line4 + 2);
    for (int i = 0; i < width; i++) {
        putchar(196);
    }
    for (int i = 1; i < height; i++) {
        Console::gotoXY(line3, top + i);
        putchar(179);
    }
    Console::gotoXY(line3, line1 + 2);
    putchar(197);

    // Write information into the board
    Console::setColor(WHITE, BLACK);
    Console::gotoXY(left + 3, top + 2);
    std::cout << "KEYS:";
    Console::gotoXY(left + 20, top + 1);
    putchar(249);
    cout << "Up arrow: to move up";
    Console::gotoXY(left + 52, top + 1);
    putchar(249);
    cout << "Down arrow: to move down";
    Console::gotoXY(left + 20, top + 3);
    putchar(249);
    cout << "Left arrow: to move left";
    Console::gotoXY(left + 52, top + 3);
    putchar(249);
    cout << "Right arrow: to move right";
    Console::gotoXY(left + 83, top + 1);
    putchar(249);
    cout << "Enter: to select or deselect a cell.";
    Console::gotoXY(left + 83, top + 3);
    putchar(249);
    cout << "A: to assist you by making suggestion.";
    Console::gotoXY(left + 20, top + 5);
    putchar(249);
    cout << "S: to shuffle the board.";
    Console::gotoXY(left + 52, top + 5);
    putchar(249);
    cout << "I: for more infomation.";
    Console::gotoXY(left + 83, top + 5);
    putchar(249);
    cout << "ESC: to exit the program safely.";


    Console::gotoXY(left + 3, top + 10);
    cout << "Rules:";
    Console::gotoXY(left + 17, top + 7);
    int left1 = left + 17;
    putchar(249);
    cout << "Pikachu Game (also known as the Pikachu Onet Connect Animal) includes a board of multiple cells, each";
    Console::gotoXY(left1 + 1 , top + 8);
    cout << "of which presents letters from A to Z.";
    Console::gotoXY(left1, top + 10);
    putchar(249);
    cout << "The player have to find out and match a pair of cells which contain the same feature and connect them";
    Console::gotoXY(left1 + 1, top + 11);
    cout << "in I, L, Z or U pattern.";
    Console::gotoXY(left1, top + 13);
    putchar(249);
    cout << "If the match is legal, two cells will disappear. The game ends when all valid pairs are found.";
    Console::gotoXY(left1 + 1, top + 14);
    cout << "A valid pair satisfies two conditions: connectable and identical.";


    Console::gotoXY(left + 3, top + 17);
    cout << "Score:";
    Console::gotoXY(left + 17, top + 16);
    putchar(249);
    cout << "The game start with 0 points. And you can't have minus point.";
    Console::gotoXY(left + 17, top + 17);
    putchar(249);
    cout << "Any valid pair of cell is found give you 2 points.";
    Console::gotoXY(left + 17, top + 18);
    putchar(249);
    cout << "There is play time count for each attempt but no penalty.";
    Console::gotoXY(left + 17, top + 19);
    putchar(249);
    cout << "Any help like shuffle manually or move suggestion would decrease your point by 2.";

    Console::gotoXY(left + 1, line5 + 2);
    for (int i = 0; i < width; i++) {
        putchar(196);
    }
    Console::gotoXY(line3, line5 + 2);
    putchar(197);
    Console::gotoXY(line3, line4 + 2);
    putchar(197);

    Console::gotoXY(left + 3, top + 22);
    cout << "About us:";
    Console::gotoXY(left + 17, top + 21);
    putchar(249);
    cout << "We are first-year students in academic year 2022 - 2023. And we're from IT department (FIT) of";
    Console::gotoXY(left + 18, top + 22);
    cout << "Viet Nam National University Ho Chi Minh City - University of Science (VNUHCM-US).";
    Console::gotoXY(left + 17, top + 24);
    putchar(249);
    cout << "Name: Tran Huy Khanh                    Student ID: 22127191                    Class: 22CLC03";
    Console::gotoXY(left + 17, top + 25);
    putchar(249);
    cout << "Name: Hoang Bao Khanh                   Student ID: 22127183                    Class: 22CLC03";

    Console::gotoXY(left + 17, top + 27);
    putchar(249);
    cout << "This game is Programming technique class project which begins in March 21st, 2023.";

    Console::setColor(WHITE, BLACK);
    Menu::printRectangle(59, 32, 23, 2);
    Console::gotoXY(60, 33);
    cout << "Press any key to return";

    int key = _getch();
    system("cls");
    return;
}

void Menu::winScreen(Account account) {
    srand((unsigned int)time(NULL));
    Console::playSound(WIN_SOUND);
    Console::setColor(WHITE, GREEN);
    cout << R"(
                             __________  _   ____________  ___  ________  ____    ___  ______________  _   _______
                            / ____/ __ \/ | / / ____/ __ \/   |/_  __/ / / / /   /   |/_  __/  _/ __ \/ | / / ___/
                           / /   / / / /  |/ / / __/ /_/ / /| | / / / / / / /   / /| | / /  / // / / /  |/ /\__ \ 
                          / /___/ /_/ / /|  / /_/ / _, _/ ___ |/ / / /_/ / /___/ ___ |/ / _/ // /_/ / /|  /___/ / 
                          \____/\____/_/ |_/\____/_/ |_/_/  |_/_/  \____/_____/_/  |_/_/ /___/\____/_/ |_//____/  
                                                                                        
	)";

    Console::setColor(WHITE, RED);
    Console::gotoXY(55, 8);
    cout << "BRAVO !!! YOU FINISHED THE GAME";

    Console::gotoXY(59, 10);
    cout << "YOUR SCORE: " << account.score << ".";
    Console::gotoXY(59, 11);
    cout << "YOUR TIME: " << account.time << "s.";
    Console::gotoXY(47, 12);
    cout << "GO TO LEADER BOARD TO SEE IF YOUR NAME HERE!!!";

    int loop = 30;
    while (loop--) {
        Console::setColor(WHITE, RED);
        drawFaceRightPikachu();
        Console::setColor(WHITE, rand() % 7);
        Console::gotoXY(30, 18);
        cout << R"(
                                                                                      .''.       
                                                          .''.      .        *''*    :_\/_:     . 
                                                         :_\/_:   _\(/_  .:.*_\/_*   : /\ :  .'.:.'.
                                                     .''.: /\ :   ./)\   ':'* /\ * :  '..'.  -=:o:=-
                                                    :_\/_:'.:::.    ' *''*    * '.\'/.' _\(/_'.':'.'
                                                    : /\ : :::::     *_\/_*     -= o =-  /)\    '  *
                                                     '..'  ':::'     * /\ *     .'/.\'.   '
                                                                 *            *..*         :
                                                                       *
                                                          *
		)";
        Console::setColor(WHITE, RED);
        drawFaceLeftPikachu();
        Sleep(200);
    }
    Console::setColor(WHITE, BLACK);
    std::system("cls");
}

void Menu::continueScreen() {
    Console::gotoXY(5, 0);
    cout << R"(
                                        _._       _,._
                                    _.'   `. ' .'   _`.
                            ,"""/`""-.-.,/. ` V'\-,`.,--/"""."-..
                          ,'    `...,' . ,\-----._|     `.   /   \
                         `.            .`  -'`"" .._   :> `-'   `.
                        ,'  ,-.  _,.-'| `..___ ,'   |'-..__   .._ L
                       .    \_ -'   `-'     ..      `.-' `.`-.'_ .|
                       |   ,',-,--..  ,--../  `.  .-.    , `-.  ``.
                       `.,' ,  |   |  `.  /'/,,.\/  |    \|   |
                            `  `---'    `j   .   \  .     '   j
                          ,__`"        ,'|`'\_/`.'\'        |\-'-, _,.
                   .--...`-. `-`. /    '- ..      _,    /\ ,' .--"'  ,'".
                 _'-""-    --  _`'-.../ __ '.'`-^,_`-""""---....__  ' _,-`
               _.----`  _..--.'        |  "`-..-" __|'"'         .""-. ""'--.._
              /        '    /     ,  _.+-.'  ||._'   """". .          `     .__\
             `---    /        /  / j'       _/|..`  -. `-`\ \   \  \   `.  \ `-..
            ," _.-' /    /` ./  /`_|_,-"   ','|       `. | -'`._,   L  \ .  `.   |
            `"' /  /  / ,__...-----| _.,  ,'            `|----.._`-.|' |. .` ..  .
               /  '| /.,/   \--.._ `-,' ,          .  '`.'  __,., '  ''``._ \ \`,'
              /_,'---  ,     \`._,-` \ //  / . \    `._,  -`,  / / _   |   `-L -
               /       `.     ,  ..._ ' `_/ '| |\ `._'       '-.'   `.,'     |
              '         /    /  ..   `.  `./ | ; `.'    ,"" ,.  `.    \      |
               `.     ,'   ,'   | |\  |       "        |  ,'\ |   \    `    ,L
               /|`.  /    '     | `-| '                  /`-' |    L    `._/  \
              / | .`|    |  .   `._.'                   `.__,'   .  |     |  (`
             '-""-'_|    `. `.__,._____     .    _,        ____ ,-  j     ".-'"'
                    \      `-.  \/.    `"--.._    _,.---'""\/  "_,.'     /-'
                     )        `-._ '-.        `--"      _.-'.-""        `.
                    ./            `,. `".._________...""_.-"`.          _j
                   /_\.__,"".   ,.'  "`-...________.---"     .".   ,.  / \
                          \_/"""-'                           `-'--(_,`"`-` 
)"; 
    Console::setColor(WHITE, RED);
    printRectangle(94, 14, 37, 4);
    Console::gotoXY(95, 15);
    cout << "This feature is under construction.";
    Console::gotoXY(95, 16);
    cout << "It will be available in future patch.";
    Console::gotoXY(95, 17);
    cout << "Press any button to come back...";
    Console::setColor(WHITE, BLACK);

    int key = _getch();
    Console::clearConsole();
    return;
}

void Menu::drawFaceLeftPikachu() {
    Console::gotoXY(5, 13);
    cout << R"(
	
         `;-.          ___,
           `.`\_...._/`.-"`
             \        /      ,
             /()   () \    .' `-._
            |)  .    ()\  /   _.'
            \  -'-     ,; '. <
             ;.__     ,;|   > \
            / ,    / ,  |.-'.-'
           (_/    (_/ ,;|.<`
             \    ,     ;-`
              >   \    /
             (_,-'`> .'
                  (_,'
		)";
}

void Menu::drawFaceRightPikachu() {
    Console::gotoXY(60, 13);
    cout << R"(

                                                                                                                           ,___          .-;'
                                                                                                                           `"-.`\_...._/`.`
                                                                                                                        ,      \        /
                                                                                                                     .-' ',    / ()   ()\
                                                                                                                    `'._   \  /()    .  (|
                                                                                                                        > .' ;,     -'-  /
                                                                                                                       / <   |;,     __.;
                                                                                                                       '-.'-.|  , \    , \
                                                                                                                          `>.|;, \_)    \_)
                                                                                                                           `-;     ,    /
                                                                                                                              \    /   <
                                                                                                                               '. <`'-,_)
                                                                                                                                '._)
		)";
}