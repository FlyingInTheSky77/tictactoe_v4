#include "PlayingComputer.h"

int PlayingComputer::FirstFreeCellComputerMakeNextMove(const Board_Struct& Current_Game_Board) {
	for (size_t i = 0; i < Current_Game_Board.size_; ++i)
	{
		if (Current_Game_Board.cells_[i] == Cell::empty)
		{
			m_current_number_of_move++;
			return i;
		}
	}
}

int PlayingComputer::ComputerMakeNextMove(const Board_Struct& Current_Game_Board) {	
	if (Current_Game_Board.cells_[4] == Cell::empty) {//if center if free - go in center!
		m_current_number_of_move++;
		return 4;
	}
	if (m_current_number_of_move == 0) {//if center if not free and its comp first move - go in first free corner!
		return FirstFreeCornerWithFreeVerticalAndGorizontLinesFromCorner(Current_Game_Board);
	}
	int move = CanWinNextMove(Current_Game_Board, Cell::o);//if comp can win next move - go and win
	if (move != -1) {
		return move;
	}
	move = CanWinNextMove(Current_Game_Board, Cell::x);//if player can win next move - don't give them win
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
		if (Current_Game_Board.cells_[0] == Cell::empty && CheckFreeLineFromCorner(0, Current_Game_Board)) {
			m_current_number_of_move++;
			return 0;
		}
		else if (Current_Game_Board.cells_[2] == Cell::empty && CheckFreeLineFromCorner(2, Current_Game_Board)) {
			m_current_number_of_move++;
			return 2;
		}
		else if (Current_Game_Board.cells_[6] == Cell::empty && CheckFreeLineFromCorner(6, Current_Game_Board)) {
			m_current_number_of_move++;
			return 6;
		}
		else if (Current_Game_Board.cells_[8] == Cell::empty && CheckFreeLineFromCorner(8, Current_Game_Board)) {
			m_current_number_of_move++;
			return 8;
		}
		else {
			return -1;
		}
	}

	int PlayingComputer::SimpleFirstFreeCorner(const Board_Struct& Current_Game_Board) {
		if (Current_Game_Board.cells_[0] == Cell::empty) {
			m_current_number_of_move++;
			return 0;
		}
		else if (Current_Game_Board.cells_[2] == Cell::empty) {
			m_current_number_of_move++;
			return 2;
		}
		else if (Current_Game_Board.cells_[6] == Cell::empty) {
			m_current_number_of_move++;
			return 6;
		}
		else if (Current_Game_Board.cells_[8] == Cell::empty) {
			m_current_number_of_move++;
			return 8;
		}
		else {
			return -1;
		}
	}

bool PlayingComputer::CheckFreeLineFromCorner(int Cell, const Board_Struct& Board) {
	if (Cell == 0 && (Board.cells_[1]==Cell::empty) && (Board.cells_[2] == Cell::empty) && (Board.cells_[3] == Cell::empty)&& (Board.cells_[6] == Cell::empty)) {
		m_current_move = 0;
		return true;
	}
	else if (Cell == 2 && (Board.cells_[0] == Cell::empty) && (Board.cells_[1] == Cell::empty) && (Board.cells_[5] == Cell::empty) && (Board.cells_[8] == Cell::empty)) {
		m_current_move = 2;
		return true;
	}
	else if (Cell == 6 && (Board.cells_[0] == Cell::empty) && (Board.cells_[3] == Cell::empty) && (Board.cells_[7] == Cell::empty) && (Board.cells_[6] == Cell::empty)) {
		m_current_move = 6;
		return true;
	}
	else if (Cell == 8 && (Board.cells_[2] == Cell::empty) && (Board.cells_[5] == Cell::empty) && (Board.cells_[6] == Cell::empty) && (Board.cells_[7] == Cell::empty)) {
		m_current_move = 8;
		return true;
	}
}

int PlayingComputer::CanWinNextMove(const Board_Struct& Board, const Cell& Player_Symbol) {
	const size_t Side = Board.side_;
	//Check gorizontal lines
	for (size_t i = 0; i < Side; i++) { 
		if ((Board.cells_[i * Side] == Player_Symbol) && (Board.cells_[i * Side + 1] == Cell::empty) && (Board.cells_[i * Side + 2] == Player_Symbol)) {
			return (i * Side + 1);
		}
		else if ((Board.cells_[i * Side] == Cell::empty) && (Board.cells_[i * Side + 1] == Player_Symbol) && (Board.cells_[i * Side + 2] == Player_Symbol)) {
			return (i * Side);
		}
		else if ((Board.cells_[i * Side] == Player_Symbol) && (Board.cells_[i * Side + 1] == Player_Symbol) && (Board.cells_[i * Side + 2] == Cell::empty)) {
			return (i * Side + 2);
		}
	}
	// Check vertical lines
	for (size_t i = 0; i < Side; i++) { 
		if ((Board.cells_[i] == Cell::empty) && (Board.cells_[i + Side] == Player_Symbol) && (Board.cells_[i + Side * 2] == Player_Symbol)) {
			return i;
		}
		else if ((Board.cells_[i] == Player_Symbol) && (Board.cells_[i + Side] == Cell::empty) && (Board.cells_[i + Side * 2] == Player_Symbol)) {
			return i + Side;
		}
		else if ((Board.cells_[i] == Player_Symbol) && (Board.cells_[i + Side] == Player_Symbol) && (Board.cells_[i + Side * 2] == Cell::empty)) {
			return i + Side * 2;
		}
	}
	// Check one diagonal lines
	if ((Board.cells_[0] == Cell::empty) && (Board.cells_[4] == Player_Symbol) && (Board.cells_[8] == Player_Symbol)) {
		return 0;
	}
	else if ((Board.cells_[0] == Player_Symbol) && (Board.cells_[4] == Cell::empty) && (Board.cells_[8] == Player_Symbol)) {
		return 4;
	}
	else if ((Board.cells_[0] == Player_Symbol) && (Board.cells_[4] == Player_Symbol) && (Board.cells_[8] == Cell::empty)) {
		return 8;
	}
	//Check second diagonal lines
	else if ((Board.cells_[6] == Cell::empty) && (Board.cells_[4] == Player_Symbol) && (Board.cells_[2] == Player_Symbol)) {
		return 6;
	}
	else if ((Board.cells_[6] == Player_Symbol) && (Board.cells_[4] == Cell::empty) && (Board.cells_[2] == Player_Symbol)) {
		return 4;
	}
	else if ((Board.cells_[6] == Player_Symbol) && (Board.cells_[4] == Player_Symbol) && (Board.cells_[2] == Cell::empty)) {
		return 2;
	}
    return -1;
}