#pragma once

enum  class Player { first, second, comp };

enum class Game_Type {TwoPlayersOnOneKeyboard, PlayerVSComputer};

enum class Move_Status { move_done, cell_bussy, move_is_not_start };

struct Board_Struct {
	int size;
	char* Cells_Char;
};

struct Board_Info {
	int size;
	int side;
};
