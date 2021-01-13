#include "Control.h"


Control::Control(Game_Board& Current_Game_Board, View& Current_View_Model) :
    m_Current_Game_Board(Current_Game_Board),
    m_View(Current_View_Model),
    m_first_move_done(false),
    m_Current_Player(Player::first)
{
    m_GameScore.First_Player_Score = 0;
    m_GameScore.Second_Player_Score = 0;
    m_View.SetBoardInfo(m_Current_Game_Board.GetBoardInfo());
    m_View.DrawWikiBoardAndSectionHeaders(m_Game_Type);
    m_View.ShowScore(m_GameScore.First_Player_Score, m_GameScore.Second_Player_Score);
    m_uniq_ptr_Playing_Computer = std::make_unique <PlayingComputer>();
}

void Control::SelectGameType() {
    m_Game_Type = m_View.PlayerSelectGameType();
    if (m_Game_Type == Game_Type::PlayerVSComputer) {
        m_ptr_Playing_Computer = new PlayingComputer;
        m_uniq_ptr_Playing_Computer;
        m_View.DrawScoreHeadersGameWithComp();
    }
}

void Control::GameCicle() {
    bool Wanna_Play_More = true;
    do {
        CurrentGameFunction();
        m_View.PrintWannaPlayOrExitGameMessage("Wanna play more - press \"1\", else - any key");
        Wanna_Play_More = m_View.PlayOneMoreTimeFunction();
    } while (Wanna_Play_More);
    m_View.ClearImportantMessageIfExist();
    m_View.PrintWannaPlayOrExitGameMessage("EXIT THE GAME");
}

void Control::MakeMove(const Player& current_player) {
    Move_Status Move_Status = Move_Status::move_is_not_start;
    if (m_Game_Type == Game_Type::PlayerVSComputer && current_player == Player::second) {
        m_View.CompThinkingAndMove();
        //int next_move=m_ptr_Playing_Computer->ComputerMakeNextMove(m_Current_Game_Board.GetBoardForDraw());
        int next_move = m_uniq_ptr_Playing_Computer->ComputerMakeNextMove(m_Current_Game_Board.GetBoardForDraw());
        Move_Status = m_Current_Game_Board.MakeMoveOnBoard(next_move, ReturnPlayerMoveSymbol());
        }
    else { // for situation: m_Game_Type == Game_Type::TwoPlayersOnOneKeyboard or Second Player move in any Game_Type
        while (Move_Status != Move_Status::move_done) {
            int next_move = m_View.NextMove(m_Current_Player);
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
        m_Current_Player = Player::first;
        m_first_move_done = true;
    }
    else if (m_Current_Player == Player::first) {
        m_Current_Player = Player::second;
    }
    else {
        m_Current_Player = Player::first;
    }
}

char Control::ReturnPlayerMoveSymbol() {
    if (m_Current_Player == Player::first) {
        return 'x';
    }
    else {
        return 'o';
    }
}

void Control::CurrentGameFunction() {
    m_Current_Game_Board.InitializeBlankTictactoeBoard();
    m_first_move_done = false;
    m_View.DrawBoard(m_Current_Game_Board.GetBoardForDraw());
    do {
        SetNextPlayer();
        MakeMove(m_Current_Player);
        m_View.DrawBoard(m_Current_Game_Board.GetBoardForDraw());
    } while (!IsGameOver());
}

bool Control::IsGameOver() {
    if (m_Current_Game_Board.IsWinner(m_Current_Player)) {
        Scoring();
        m_View.ShowWinner(m_Current_Player);
        return true;
    }
    else if (m_Current_Game_Board.IsDraw()) {
        m_View.ShowDrawStatus();
        return true;
    }
    else {
        return false;
    }
}

void Control::Scoring() {
    if (m_Current_Player == Player::first) {
        m_GameScore.First_Player_Score++;
    }
    else {
        m_GameScore.Second_Player_Score++;
    }
    m_View.ShowScore(m_GameScore.First_Player_Score, m_GameScore.Second_Player_Score);
}