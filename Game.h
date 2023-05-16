#pragma once

#include "Board.h"
#include "Score.h"


class Game
{
public:
	Game(size_t board_column_number, size_t board_row_number);
	void select_cell(size_t x, size_t y);

	bool is_over();
	const Board& get_board() const;
	const Score& get_score() const;
	bool get_quit();
	bool get_reset();
	void set_reset(bool reset);
	void set_quit(bool quit);

private:
	size_t MinimalBlockSize{ 2 };

	Board _board;
	Score _score;
	bool _game_over = false;
	bool _reset = false;
	bool _quit = false;

	bool check_moves();
};