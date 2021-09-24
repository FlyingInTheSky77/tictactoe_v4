#pragma once

#include "EnumVariables.h"

class Game_Board
{
public:    
    Game_Board();
    bool IsDraw();
    bool IsWinner( Player player );
    Move_Status MakeMoveOnBoard( const int& move, const Cell& player_move_symbol );
    Board_Struct GetBoardForDraw();
    void InitializeBlankTictactoeBoard();    
    Board_Struct GetBoardInfo();

private:
    const int board_size_ = 9;
    Board_Struct board_;
    
    bool IsCellFreeForMove( const int& move );
    Cell GetCellFromPlayer( const Player& player );
    
};