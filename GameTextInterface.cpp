#include "GameTextInterface.h"

#include <iostream>
#include <limits>
#include <ostream>


GameTextInterface::GameTextInterface(Game& game) : IGameInterface(game)
{
}

void GameTextInterface::compute_game_logic()
{
	const auto key{ std::getchar() };

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	switch (tolower(key))
	{
	case 'a':
		if (_game.is_over() || _cursor.get_x() == 0)
		{
			break;
		}
		else
		{
			_cursor.move_left();
			break;
		}
	case 's':
		if (_game.is_over() || _cursor.get_y() == _game.get_board().get_rows_count() - 1)
		{
			break;
		}
		else
		{
			_cursor.move_down();
			break;
		}
	case 'd':
		if (_game.is_over() || _cursor.get_x() == _game.get_board().get_columns_count() - 1)
		{
			break;
		}
		else
		{
			_cursor.move_right();
			break;
		}
	case 'w':
		if (_game.is_over() || _cursor.get_y() == 0)
		{
			break;
		}
		else
		{
			_cursor.move_up();
			break;
		}
	case 'f':
		_game.select_cell(_cursor.get_x(), _cursor.get_y());
		if (_game.is_over())
		{
			_cursor.set_x(static_cast<int>(_game.get_board().get_columns_count()));
			_cursor.set_y(static_cast<int>(_game.get_board().get_rows_count()));
		}
		break;
	case 'r':
		_game.set_reset(true);
		break;
	case 'q':
		_game.set_quit(true);
		break;
	default:
		break;
	};
}


std::ostream& operator<<(std::ostream& os, const Color& color)
{
	switch (color)
	{
	case Color::blue:
		os << "\033[1;34m";
		break;
	case Color::green:
		os << "\033[1;32m";
		break;
	case Color::magenta:
		os << "\033[1;35m";
		break;
	case Color::red:
		os << "\033[1;31m";
		break;
	case Color::yellow:
		os << "\033[1;33m";
		break;
	default:
		return os;
		break;
	}

	return os << "o\033[0m";
}

void GameTextInterface::print_game()
{
	system("cls");

	int x_counter{};
	int y_counter{};

	std::cout << std::endl << "Total score: " << _game.get_score().total_score << std::endl;

	for (const auto& cell : _game.get_board().get_cells())
	{
		if (cell.is_selected())
		{
			std::cout << "\033[43m";
		}

		if (_cursor.get_x() == x_counter && _cursor.get_y() == y_counter)
		{
			std::cout << "\033[47m";
		}

		if (cell.get_color() == Color::none)
		{
			std::cout << ' ';
		}
		else
		{
			std::cout << cell.get_color();
		}

		std::cout << "\033[0m ";

		if (++x_counter == _game.get_board().get_columns_count())
		{
			std::cout << std::endl;

			x_counter = 0;
			++y_counter;
		}
	}
	std::fill_n(std::ostreambuf_iterator<char>{ std::cout }, _game.get_board().get_columns_count() * 2 - 1, '-');
	std::cout << std::endl << "(x,y): (" << _cursor.get_x() << "," << _cursor.get_y() << ")" << std::endl;

	if (_game.is_over())
	{
		std::cout << "XXX GAME OVER XXX " << std::endl;
	}
	else
	{
		std::cout << "Block score: " << _game.get_score().block_score << std::endl;
	}
}
