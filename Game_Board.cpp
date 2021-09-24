#include "Game_Board.h"

Game_Board::Game_Board()
    : board_( board_size_ )
{ }

Board_Struct Game_Board::GetBoardInfo() {
    return board_;
}

void Game_Board::InitializeBlankTictactoeBoard() {
    board_.clearBoard();
}

bool Game_Board::IsDraw() {
    for ( size_t i = 0; i < board_.size_; ++i ) {
        if ( board_.cells_[i] == Cell::empty ) {
            return false;
        }
    }
    return true;
}

bool Game_Board::IsWinner( Player player ) {
    Cell Current_Cell = GetCellFromPlayer( player );
    const size_t Board_Side = board_.side_;
    //   Check gorizontal lines
    for ( size_t i = 0; i < Board_Side; i++ ) { 
        if ( ( board_.cells_[i * Board_Side] == Current_Cell ) && ( board_.cells_[i * Board_Side + 1] == Current_Cell ) && ( board_.cells_[i * Board_Side + 2] == Current_Cell ) ) {
            return true;
        }
    }
    //   Check vertical lines
    for (size_t i = 0; i < Board_Side; i++) {
        if ((board_.cells_[i] == Current_Cell) && (board_.cells_[i + Board_Side] == Current_Cell) && (board_.cells_[i + Board_Side * 2] == Current_Cell)) {
            return true;
        }
    }
    //  Check diagonal lines
    if ((board_.cells_[0] == Current_Cell) && (board_.cells_[4] == Current_Cell) && (board_.cells_[8] == Current_Cell)) {
        return true;
    }

    else if ((board_.cells_[6] == Current_Cell) && (board_.cells_[4] == Current_Cell) && (board_.cells_[2] == Current_Cell)) {
        return true;
    }
    return false;
}

bool Game_Board::IsCellFreeForMove( const int& cell ) {
    if ( ( static_cast<size_t>(cell) >= board_.size_ ) || ( cell < 0 ) ) {
        return false;
    }

    if ( board_.cells_[cell] == Cell::empty )
        return true;

    return false;
}

 Move_Status Game_Board::MakeMoveOnBoard( const int& move, const Cell& player_move_symbol ) {
    if (!IsCellFreeForMove(move)) {
        return Move_Status::cell_bussy;
    }

    board_.cells_[move] = player_move_symbol;
    return Move_Status::move_done;
}

Board_Struct Game_Board::GetBoardForDraw(){
    return board_;
}

Cell Game_Board::GetCellFromPlayer(const Player& player) {
    if (player == Player::first) {
        return Cell::x;
    }
    else {
        return Cell::o;
    }
}
