#include "Control.h"

Control::Control(Game_Type type, View view)
    : m_first_move_done( false )
    , Current_Player_(Player::first)
 {  
    m_GameScore.First_Player_Score = 0;
    m_GameScore.Second_Player_Score = 0;
    m_View.ShowScore(m_GameScore.First_Player_Score, m_GameScore.Second_Player_Score);
    if (type == Game_Type::PlayerVSComputer) {
        m_Game_Type = Game_Type::PlayerVSComputer;
        m_uniq_ptr_Playing_Computer = std::make_unique <PlayingComputer>();
        m_View.DrawScoreHeadersGameWithComp();
    }
}

void Control::MakeMove(const Player& current_player) {
    Move_Status Move_Status = Move_Status::move_is_not_start;
    if (m_Game_Type == Game_Type::PlayerVSComputer && current_player == Player::second) {
        m_View.CompThinkingAndMove();
        int next_move = m_uniq_ptr_Playing_Computer->ComputerMakeNextMove(m_Current_Game_Board.GetBoardForDraw());
        Move_Status = m_Current_Game_Board.MakeMoveOnBoard(next_move, ReturnPlayerMoveSymbol());
        }
    // for situation: m_Game_Type == Game_Type::TwoPlayersOnOneKeyboard or Second Player move in any Game_Type
    else { 
        while (Move_Status != Move_Status::move_done) {
            int next_move = m_View.NextMove(Current_Player_);
            Move_Status = m_Current_Game_Board.MakeMoveOnBoard(next_move, ReturnPlayerMoveSymbol());
            if (Move_Status == Move_Status::cell_bussy)
            {
                m_View.PrintImportantMessage("Cell is bussy. Try one more time");
            }
        }
    }
}

void Control::SetNextPlayer() {
    if (m_first_move_done == false)
    {
        Current_Player_ = Player::first;
        m_first_move_done = true;
    }
    else if (Current_Player_ == Player::first) {
        Current_Player_ = Player::second;
    }
    else {
        Current_Player_ = Player::first;
    }
}

Cell Control::ReturnPlayerMoveSymbol() {
    if (Current_Player_ == Player::first) {
        return Cell::x;
    }
    return Cell::o;
}

void Control::CurrentGameFunction() {
    m_Current_Game_Board.InitializeBlankTictactoeBoard();    
    m_first_move_done = false;
    m_View.DrawBoard(m_Current_Game_Board.GetBoardForDraw());
    do {
        SetNextPlayer();
        MakeMove(Current_Player_);
        m_View.DrawBoard(m_Current_Game_Board.GetBoardForDraw());
    } while (!IsGameOver());
}

bool Control::IsGameOver() {
    if (m_Current_Game_Board.IsWinner(Current_Player_)) {
        Scoring();
        m_View.ShowWinner(Current_Player_);
        return true;
    }
    else if (m_Current_Game_Board.IsDraw()) {
        m_View.ShowDrawStatus();
        return true;
    }
    return false;
}

void Control::Scoring() {
    if (Current_Player_ == Player::first) {
        m_GameScore.First_Player_Score++;
    }
    else {
        m_GameScore.Second_Player_Score++;
    }
    m_View.ShowScore(m_GameScore.First_Player_Score, m_GameScore.Second_Player_Score);
}