#pragma once
#include "stdafx.h"
//#include "EnumVariables.h"
#include "Game_Board.h"
#include "View.h"
#include "PlayingComputer.h"

class Control {
public:
	Control(Game_Board& Current_Game_Board, View& Current_View_Model);
	void SelectGameType();
	void GameCicle();
	void CurrentGameFunction();
	void MakeMove(const Player& current_player);
	void SetNextPlayer();
	bool IsGameOver();
	struct Score {
		int First_Player_Score;
		int Second_Player_Score;
	};
	//~Control() {
	//	delete m_ptr_Playing_Computer;
	//}
private:
	char ReturnPlayerMoveSymbol();
	void Scoring();
	Game_Board& m_Current_Game_Board;
	View& m_View;
	Player m_Current_Player;
	Score m_GameScore;
	bool m_first_move_done;
	Game_Type m_Game_Type;
	PlayingComputer* m_ptr_Playing_Computer;
	std::unique_ptr <PlayingComputer> m_uniq_ptr_Playing_Computer;

};

