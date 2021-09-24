#pragma once

#include <vector>
#include <math.h>

enum  class Player { first, second, comp };

enum class Game_Type { TwoPlayersOnOneKeyboard, PlayerVSComputer };

enum class Move_Status { move_done, cell_bussy, move_is_not_start };

enum class Cell { o, x, empty };

struct Board_Struct {
	Board_Struct( size_t size )
		: size_( size )
		, side_(static_cast<size_t>(sqrt(size_)))
	{
		for ( size_t i = 0; i < size_; ++i ) {
			cells_.push_back( Cell::empty );
		}
	}
	size_t size_;
	size_t side_;
	std::vector< Cell > cells_;
	void clearBoard() {
		cells_.clear();
		for ( size_t i = 0; i < size_; ++i ) {
			cells_.push_back( Cell::empty );
		}
	}	
};

