#pragma once

#define GOTOUSERINPUTPOS moveCursorTo(0, rowSize + 1); clearCurrentLine();

#define GOTOCONSOLEINPUTPOS moveCursorTo(0, rowSize + 2); clearCurrentLine();

#define GOTOKEYBOARDPOS moveCursorTo(0, rowSize + 5); clearCurrentLine();


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <cctype>
#include <unordered_map>
#include <Windows.h>

class Words
{
private:
    enum Colloring {
        white = 7, green = 10, yellow = 14, red = 12
    };
    struct Veci
    {
        int x;
        int y;
        char c;
    };
    void moveCursorTo(int x, int y);
    void clearCurrentLine();
    void clearScreen();
public:
    Words();
    std::string getWordData(int index);
    std::string returnRandomWord();
    bool checkWinCondition(std::string& input, std::string& goal);
    void drawKeyboard();
    void updateKeyboard();
    void drawEmptyBoard();
    void updateBoard(std::string input, std::string goal);
    void drawBoard();
    void runGame();


private:
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    const int boardStartY = 5;
    int lives = 7;
    const int rowSize = lives;
    int currentLine = 0;
    static constexpr int goalsize = 5;
    int gridsize = goalsize * lives;
    
    std::vector<std::string> words;
    std::vector<std::string> egooglewords;
    std::string keyboard = R"(
        Q W E R T Y U I O P
        A S D F G H J K L
        Z X C V B N M )";
    std::unordered_map<char, Colloring> charcol;
    std::vector<std::string> wordlegrid = std::vector<std::string>(lives, std::string(goalsize, '_'));
    std::vector<Colloring> wordlegridcolor;
    std::string targetword;
    std::ifstream ineasy;
    std::ifstream inallwords;




};