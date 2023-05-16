#include "Game.h"

#include "Board.h"


Game::Game(size_t board_column_number, size_t board_row_number) : _board {board_column_number, board_row_number }
{
}

void Game::select_cell(size_t x, size_t y)
{
	if (!_game_over)
	{
		if (_board.get_cell(x,y).is_selected())
		{
			_score.total_score += _score.block_score;
			_score.block_score = 0;
			_board.pop_selected_cells();
			_board.collapse_column();
			_board.move_column();
			_game_over = !check_moves();
		}
		else
		{
			_board.deselect_cells();
			size_t selected_cells = _board.select_cells(x, y);

			if (selected_cells < MinimalBlockSize)
			{
				_board.deselect_cells();
			}
			else
			{
				_score.block_score = calculate_block_score(selected_cells);
			}
		}
	}
}

bool Game::is_over()
{
	return _game_over;
}

const Board& Game::get_board() const
{
	return _board;
}
const Score& Game::get_score() const
{
	return _score;
}

bool Game::get_quit()
{
	return _quit;
}

bool Game::get_reset()
{
	return _reset;
}

void Game::set_reset(bool reset)
{
	_reset = reset;
}

void Game::set_quit(bool quit)
{
	_quit = quit;
}

bool Game::check_moves()
{
	for (size_t row = 0; row < _board.get_rows_count(); ++row)
	{
		for (size_t col = 0; col < _board.get_columns_count(); ++col)
		{
			if (_board.select_cells(col, row) >= MinimalBlockSize)
			{
				_board.deselect_cells();
				return true;
			}
		}
	}
	_board.deselect_cells();
	return false;
}