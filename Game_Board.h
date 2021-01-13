#pragma once

#include "stdafx.h"
#include <math.h>
#include "EnumVariables.h"

class Game_Board
{
public:
    enum class Cell { o, x, empty };
    Game_Board();
    bool IsDraw();
    bool IsWinner(Player player);
    Move_Status MakeMoveOnBoard(const int& Move_In_Cell, const char& Cell_Char);
    Board_Struct GetBoardForDraw();
    void InitializeBlankTictactoeBoard();
    Cell GetCellFromPlayer(const Player& player);
    Board_Info GetBoardInfo();
private:
    char ConvertCellToChar(const Cell& Cell);
    Cell ConvertCharToCell(char Cell_Char);
    bool IsCellFreeForMove(const int& My_Cell_Number);
    static const int m_Board_Size = 9;
    Cell m_Cells[m_Board_Size];

};

