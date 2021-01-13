// tictactoe_v4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "stdafx.h"
#include "View.h"
#include "Game_Board.h"
#include "Control.h"
#include "EnumVariables.h"

int main()
{
    Game_Board My_Game_Board;
    View Game_View;
    Control My_Game_control(My_Game_Board, Game_View);
    My_Game_control.SelectGameType();
    My_Game_control.GameCicle();
}
