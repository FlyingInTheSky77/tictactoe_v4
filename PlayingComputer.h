#pragma once

#include "EnumVariables.h"

class PlayingComputer
{
public:
	PlayingComputer()
		: m_current_number_of_move (0)
		{};
	int FirstFreeCellComputerMakeNextMove( const Board_Struct& Current_Game_Board );
	int ComputerMakeNextMove( const Board_Struct& Current_Game_Board );
private:
	int m_current_number_of_move;
	int m_current_move;

	bool CheckFreeLineFromCorner( int Cell_Number, const Board_Struct& Current_Game_Board );
	int CanWinNextMove( const Board_Struct& Board, const Cell& Player_Symbol );
	int FirstFreeCornerWithFreeVerticalAndGorizontLinesFromCorner( const Board_Struct& Current_Game_Board );
	int SimpleFirstFreeCorner( const Board_Struct& Current_Game_Board );
};

