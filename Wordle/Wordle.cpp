#pragma once
#include "Wordle.h"
#include <cassert>

void Words::moveCursorTo(int x, int y)
{
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Words::clearCurrentLine()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // Get current cursor position
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD cursorPos = csbi.dwCursorPosition;

    DWORD written;
    FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X, { 0, cursorPos.Y }, &written);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, csbi.dwSize.X, { 0, cursorPos.Y }, &written);

    // Move cursor back to beginning of the line
    SetConsoleCursorPosition(hConsole, { 0, cursorPos.Y });
}

void Words::clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD cellsWritten;
    DWORD consoleSize;
    COORD topLeft = { 0, 0 };

    // Get the number of character cells in the current buffer
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    consoleSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with spaces
    FillConsoleOutputCharacter(hConsole, ' ', consoleSize, topLeft, &cellsWritten);

    // Fill the entire screen with the current text attributes
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, topLeft, &cellsWritten);

    // Move the cursor to the top-left corner
    SetConsoleCursorPosition(hConsole, topLeft);
}


Words::Words()
{
    inallwords.open("valid-wordle-words.txt");
    if (!inallwords.is_open()) {
        std::cerr << "Failed to open file.\n";
        return;
    }
    std::string line;
    std::stringstream strstream;
    while (getline(inallwords, line))
    {
        words.push_back(line);
    }

    inallwords.close();

    ineasy.open("finishedlist.txt");
    if (!ineasy.is_open()) {
        std::cerr << "Failed to open file.\n";
        return;
    }
    for (int stindex = 0; getline(ineasy, line); stindex++)
    {
        egooglewords.push_back(line);
    }

    ineasy.close();

}

std::string Words::getWordData(int index)
{
    targetword = "No words inside the file";
    int stindex = 0;
    for (const auto& w : egooglewords) {
        if (stindex == index) {
            return w;
        }
        stindex++;
    }

    return targetword;
}

std::string Words::returnRandomWord()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(egooglewords.size() - 1));

    int index = dist(rng);

    return getWordData(index);
}

bool Words::checkWinCondition(std::string& input, std::string& goal)
{
    for (int i = 0; i < input.size(); i++) {
        if (input[i] != goal[i]) return false;
    }
    return true;
}


void Words::drawKeyboard()
{
    GOTOKEYBOARDPOS
            for (int i = 0; i < keyboard.size(); i++)
            {
                std::cout << keyboard[i];
            }
    GOTOUSERINPUTPOS
}

void Words::updateKeyboard()
{
    GOTOKEYBOARDPOS
        for (const auto& c : keyboard)
        {
            if (charcol.find(c) != charcol.end())
            {
                SetConsoleTextAttribute(h, charcol[c]);
                std::cout << c;
            }
            else
            {
                SetConsoleTextAttribute(h, white);
                std::cout << c;
            }

        }
    SetConsoleTextAttribute(h, white);
    GOTOUSERINPUTPOS
}





void Words::drawEmptyBoard()
{
    for (const auto& line : wordlegrid)
    {
        std::cout << line << std::endl;
    }
}

void Words::updateBoard(std::string input, std::string goal)
{
    for (int i = 0; i < goal.size(); i++) {
        if (goal[i] == input[i])
        {
            wordlegridcolor.emplace_back(green);
            wordlegrid[currentLine][i] = input[i];

        }

        else if (goal.find(input[i]) != std::string::npos) {
            wordlegridcolor.emplace_back(yellow);
            wordlegrid[currentLine][i] = input[i];
        }

        else {
            wordlegridcolor.emplace_back(red);
            wordlegrid[currentLine][i] = input[i];
        }
    }
    currentLine++;
    moveCursorTo(0, 0 + currentLine);
    drawBoard();
}

void Words::drawBoard()
{
    int index = 0;
    for (const auto& c : wordlegrid[currentLine - 1])
    {
        if (index < wordlegridcolor.size())
        {
            int currentcolorpos = index + goalsize * (currentLine - 1);
            SetConsoleTextAttribute(h, wordlegridcolor[currentcolorpos] << 4);
            charcol[toupper(c)] = wordlegridcolor[currentcolorpos];
        }
        std::cout << c;
        index++;
    }
    std::cout << '\n';
    SetConsoleTextAttribute(h, white);
    GOTOUSERINPUTPOS
}

void Words::runGame()
{
    std::string goal = returnRandomWord();
    // 3 Conditions | if letter is not matching = R | if letter is in word && letter is not in any other or the right pos = Y | if letter is in right pos = G
    std::string input;
    wordlegridcolor.reserve(gridsize);

    std::cout << "The word is " << goal.size() << " chars big" << std::endl;
    drawEmptyBoard();
    drawKeyboard();
    while (lives > 0) {
        getline(std::cin, input);

        if (std::find(wordlegrid.begin(), wordlegrid.end(), input) != wordlegrid.end())
        {
            GOTOCONSOLEINPUTPOS
            std::cout << "Already used this word. Try again?";
            GOTOUSERINPUTPOS
            continue;
        }
        if (std::find(words.begin(), words.end(), input) == words.end())
        {
            GOTOCONSOLEINPUTPOS
            std::cout << "Invalid word! Try again?";
            input.clear();
            GOTOUSERINPUTPOS
            continue;
        }

        GOTOCONSOLEINPUTPOS
        updateBoard(input, goal);
        drawBoard();
        updateKeyboard();


        if (!checkWinCondition(input, goal))
        {
            lives--;
            continue;
        }
        else {
            while (input != "new")
            {
                GOTOCONSOLEINPUTPOS
                std::cout << "\nCongrats!! You guessed the word correctly!! : " << goal << std::endl;
                std::cout << "Type new for new game : " << std::endl;
                clearCurrentLine();
                getline(std::cin, input);
            }
                    input.clear();
                    charcol.clear();
                    wordlegrid = std::vector<std::string>(lives, std::string(goalsize, '_'));
                    wordlegridcolor.clear();
                    currentLine = 0;
                    clearScreen();
                    runGame();
            }
        }
    if (lives == 0)
    {
        std::cout << "Too bad, you lost:(. The word was : " << goal << std::endl;
    }
}
