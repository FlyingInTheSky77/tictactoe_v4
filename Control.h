#pragma once

#include <memory>

#include "EnumVariables.h"
#include "Game_Board.h"
#include "View.h"
#include "PlayingComputer.h"


class Control {
public:
	Control(Game_Type type, View view);
	void CurrentGameFunction();
	void MakeMove(const Player& current_player);
	void SetNextPlayer();
	bool IsGameOver();
	struct Score {
		int First_Player_Score;
		int Second_Player_Score;
	};

private:
	Cell ReturnPlayerMoveSymbol();
	void Scoring();
	Game_Board m_Current_Game_Board;
	View m_View;
	Player Current_Player_;
	Score m_GameScore;
	bool m_first_move_done;
	Game_Type m_Game_Type;
	std::unique_ptr < PlayingComputer > m_uniq_ptr_Playing_Computer;
};