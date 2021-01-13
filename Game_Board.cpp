#include "Game_Board.h"

Game_Board::Game_Board() {
    InitializeBlankTictactoeBoard();
}

Board_Info Game_Board::GetBoardInfo() {
    Board_Info Current_Board_info;
    Current_Board_info.side = static_cast<int>(sqrt(m_Board_Size));
    Current_Board_info.size = m_Board_Size;
    return Current_Board_info;
}

void Game_Board::InitializeBlankTictactoeBoard() {
    for (auto& item : m_Cells) {
        item = Cell::empty;
    }
}

bool Game_Board::IsDraw() {
    for (int i = 0; i < m_Board_Size; ++i) {
        if (m_Cells[i] == Cell::empty) {
            return false;
        }
    }
    return true;
}

Game_Board::Cell Game_Board::ConvertCharToCell(char Cell_Char) {
    Game_Board::Cell Current_cell = Game_Board::Cell::empty;
    if (Cell_Char == 'x') {
        Current_cell = Game_Board::Cell::x;
    }
    else if (Cell_Char == 'o') {
        Current_cell = Game_Board::Cell::o;
    }
    else if (Cell_Char == '_') {
        Current_cell = Game_Board::Cell::empty;
    }
    return Current_cell;
}

char Game_Board::ConvertCellToChar(const Cell& Cell) {
    if (Cell == Cell::o) {
        return 'o';
    }
    else if (Cell == Cell::x) {
        return 'x';
    }
    else {
        return '_';
    }
}

bool Game_Board::IsWinner(Player player) {
    Cell Current_Cell = GetCellFromPlayer(player);
    int Board_Side = static_cast<int>(sqrt(m_Board_Size));
    for (int i = 0; i < Board_Side; i++) { //Check gorizontal lines
        if ((m_Cells[i * Board_Side] == Current_Cell) && (m_Cells[i * Board_Side + 1] == Current_Cell) && (m_Cells[i * Board_Side + 2] == Current_Cell)) {
            return true;
        }
    }
    for (int i = 0; i < Board_Side; i++) { //Check vertical lines
        if ((m_Cells[i] == Current_Cell) && (m_Cells[i + Board_Side] == Current_Cell) && (m_Cells[i + Board_Side * 2] == Current_Cell)) {
            return true;
        }
    }
    //Check diagonal lines
    if ((m_Cells[0] == Current_Cell) && (m_Cells[4] == Current_Cell) && (m_Cells[8] == Current_Cell)) {
        return true;
    }
    else if ((m_Cells[6] == Current_Cell) && (m_Cells[4] == Current_Cell) && (m_Cells[2] == Current_Cell)) {
        return true;
    }
    else {
        return false;
    }
}

bool Game_Board::IsCellFreeForMove(const int& My_Cell_Number) {
    if ((My_Cell_Number >= m_Board_Size) || (My_Cell_Number < 0)) {
        return false;
    }
    else if (m_Cells[My_Cell_Number] == Cell::empty) {
        return true;
    }
    else {
        return false;
    }
}

Move_Status Game_Board::MakeMoveOnBoard(const int& Move_In_Cell, const char& Cell_Char) {
    Cell Current_Cell_To_Move = ConvertCharToCell(Cell_Char);
    if (!IsCellFreeForMove(Move_In_Cell)) {
        return Move_Status::cell_bussy;
    }
    else {
        m_Cells[Move_In_Cell] = Current_Cell_To_Move;
        return Move_Status::move_done;
    }
}

Board_Struct Game_Board::GetBoardForDraw() {
    Board_Struct Current_Board;
    Current_Board.size = m_Board_Size;
    Current_Board.Cells_Char = new char[m_Board_Size];
    for (int i = 0; i < m_Board_Size; ++i) {
        Current_Board.Cells_Char[i] = ConvertCellToChar(m_Cells[i]);
    }
    return Current_Board;
}

Game_Board::Cell Game_Board::GetCellFromPlayer(const Player& player) {
    if (player == Player::first) {
        return Cell::x;
    }
    else {
        return Cell::o;
    }
}
