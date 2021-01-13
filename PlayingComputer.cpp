#include "PlayingComputer.h"

int PlayingComputer::FirstFreeCellComputerMakeNextMove(const Board_Struct& Current_Game_Board) {
	for (int i = 0; i < Current_Game_Board.size; ++i)
	{
		if (Current_Game_Board.Cells_Char[i] == '_')
		{
			m_current_number_of_move++;
			return i;
		}
	}
}

int PlayingComputer::ComputerMakeNextMove(const Board_Struct& Current_Game_Board) {	
	if (Current_Game_Board.Cells_Char[4] == '_') {//if center if free - go in center!
		m_current_number_of_move++;
		return 4;
	}
	if (m_current_number_of_move == 0) {//if center if not free and its comp first move - go in first free corner!
		return FirstFreeCornerWithFreeVerticalAndGorizontLinesFromCorner(Current_Game_Board);
	}
	int move = CanWinNextMove(Current_Game_Board, 'o');//if comp can win next move - go and win
	if (move != -1) {
		return move;
	}
	move = CanWinNextMove(Current_Game_Board, 'x');//if player can win next move - don't give them win
	if (move != -1) {
		return move;
	}
	move = SimpleFirstFreeCorner(Current_Game_Board);
	if (move != -1) {
		return move;
	}
	else {
		return FirstFreeCellComputerMakeNextMove(Current_Game_Board);
	}
	
}

	int PlayingComputer::FirstFreeCornerWithFreeVerticalAndGorizontLinesFromCorner(const Board_Struct & Current_Game_Board) {
		if (Current_Game_Board.Cells_Char[0] == '_' && CheckFreeLineFromCorner(0, Current_Game_Board)) {
			m_current_number_of_move++;
			return 0;
		}
		else if (Current_Game_Board.Cells_Char[2] == '_' && CheckFreeLineFromCorner(2, Current_Game_Board)) {
			m_current_number_of_move++;
			return 2;
		}
		else if (Current_Game_Board.Cells_Char[6] == '_' && CheckFreeLineFromCorner(6, Current_Game_Board)) {
			m_current_number_of_move++;
			return 6;
		}
		else if (Current_Game_Board.Cells_Char[8] == '_' && CheckFreeLineFromCorner(8, Current_Game_Board)) {
			m_current_number_of_move++;
			return 8;
		}
		else {
			return -1;
		}
	}

	int PlayingComputer::SimpleFirstFreeCorner(const Board_Struct& Current_Game_Board) {
		if (Current_Game_Board.Cells_Char[0] == '_') {
			m_current_number_of_move++;
			return 0;
		}
		else if (Current_Game_Board.Cells_Char[2] == '_') {
			m_current_number_of_move++;
			return 2;
		}
		else if (Current_Game_Board.Cells_Char[6] == '_') {
			m_current_number_of_move++;
			return 6;
		}
		else if (Current_Game_Board.Cells_Char[8] == '_') {
			m_current_number_of_move++;
			return 8;
		}
		else {
			return -1;
		}
	}

bool PlayingComputer::CheckFreeLineFromCorner(int Cell, const Board_Struct& Board) {
	if (Cell == 0 && (Board.Cells_Char[1]=='_') && (Board.Cells_Char[2] == '_') && (Board.Cells_Char[3] == '_')&& (Board.Cells_Char[6] == '_')) {
		m_current_move = 0;
		return true;
	}
	else if (Cell == 2 && (Board.Cells_Char[0] == '_') && (Board.Cells_Char[1] == '_') && (Board.Cells_Char[5] == '_') && (Board.Cells_Char[8] == '_')) {
		m_current_move = 2;
		return true;
	}
	else if (Cell == 6 && (Board.Cells_Char[0] == '_') && (Board.Cells_Char[3] == '_') && (Board.Cells_Char[7] == '_') && (Board.Cells_Char[6] == '_')) {
		m_current_move = 6;
		return true;
	}
	else if (Cell == 8 && (Board.Cells_Char[2] == '_') && (Board.Cells_Char[5] == '_') && (Board.Cells_Char[6] == '_') && (Board.Cells_Char[7] == '_')) {
		m_current_move = 8;
		return true;
	}
}


int PlayingComputer::MinMax() {
	int score = 5;
	return score;
}


int PlayingComputer::CanWinNextMove(const Board_Struct& Board, const char& Player_Symbol) {
	int Side = 3;//TODO magic number - remove later
	for (int i = 0; i < Side; i++) { //Check gorizontal lines
		if ((Board.Cells_Char[i * Side] == Player_Symbol) && (Board.Cells_Char[i * Side + 1] == '_') && (Board.Cells_Char[i * Side + 2] == Player_Symbol)) {
			return (i * Side + 1);
		}
		else if ((Board.Cells_Char[i * Side] == '_') && (Board.Cells_Char[i * Side + 1] == Player_Symbol) && (Board.Cells_Char[i * Side + 2] == Player_Symbol)) {
			return (i * Side);
		}
		else if ((Board.Cells_Char[i * Side] == Player_Symbol) && (Board.Cells_Char[i * Side + 1] == Player_Symbol) && (Board.Cells_Char[i * Side + 2] == '_')) {
			return (i * Side + 2);
		}
	}
	for (int i = 0; i < Side; i++) { //Check vertical lines
		if ((Board.Cells_Char[i] == '_') && (Board.Cells_Char[i + Side] == Player_Symbol) && (Board.Cells_Char[i + Side * 2] == Player_Symbol)) {
			return i;
		}
		else if ((Board.Cells_Char[i] == Player_Symbol) && (Board.Cells_Char[i + Side] == '_') && (Board.Cells_Char[i + Side * 2] == Player_Symbol)) {
			return i + Side;
		}
		else if ((Board.Cells_Char[i] == Player_Symbol) && (Board.Cells_Char[i + Side] == Player_Symbol) && (Board.Cells_Char[i + Side * 2] == '_')) {
			return i + Side * 2;
		}
	}
	//Check one diagonal lines
	if ((Board.Cells_Char[0] == '_') && (Board.Cells_Char[4] == Player_Symbol) && (Board.Cells_Char[8] == Player_Symbol)) {
		return 0;
	}
	else if ((Board.Cells_Char[0] == Player_Symbol) && (Board.Cells_Char[4] == '_') && (Board.Cells_Char[8] == Player_Symbol)) {
		return 4;
	}
	else if ((Board.Cells_Char[0] == Player_Symbol) && (Board.Cells_Char[4] == Player_Symbol) && (Board.Cells_Char[8] == '_')) {
		return 8;
	}
	//Check second diagonal lines
	else if ((Board.Cells_Char[6] == '_') && (Board.Cells_Char[4] == Player_Symbol) && (Board.Cells_Char[2] == Player_Symbol)) {
		return 6;
	}
	else if ((Board.Cells_Char[6] == Player_Symbol) && (Board.Cells_Char[4] == '_') && (Board.Cells_Char[2] == Player_Symbol)) {
		return 4;
	}
	else if ((Board.Cells_Char[6] == Player_Symbol) && (Board.Cells_Char[4] == Player_Symbol) && (Board.Cells_Char[2] == '_')) {
		return 2;
	}
	else {
		return -1;
	}
}