#include "Board.h"

#include <cstddef>
#include <iomanip>
#include <random>
#include <vector>

#include "Color.h"
#include "Cell.h"
#include "Cursor.h"


void generate_cells(Board::cells_t& cells)
{
	static std::mt19937 generator(std::random_device{}());
	static std::uniform_int_distribution<> distribution{1, ColorCount};

	for (auto& cell : cells)
	{
		cell = Cell(static_cast<Color>(distribution(generator)));
	}
}

Board::Board(size_t columns_count, size_t rows_count) :
	_columns_count{columns_count}, _rows_count{rows_count}
{
	_cells.resize(_columns_count * _rows_count);
	generate_cells(_cells);
}

Cell& Board::get_cell(size_t column_index, size_t row_index) noexcept
{
	return _cells[row_index * get_columns_count() + column_index];
}

void Board::collapse_column()
{
	for (size_t column_index = 0; column_index < _columns_count; ++column_index)
	{
		size_t cell_pos = column_index + _rows_count;
		size_t cell_none_row = 0;

		while (cell_pos < (_columns_count * _rows_count))
		{
			if (_cells[cell_pos].get_color() == Color::none)
			{
				while (cell_pos != (column_index + cell_none_row * _rows_count))
				{
					std::swap(_cells[cell_pos - _rows_count], _cells[cell_pos]);
					cell_pos -= _rows_count;
				}
				cell_none_row++;
				cell_pos = (column_index + cell_none_row * _rows_count);
			}
			else
			{
				cell_pos += _rows_count;
			}
		}
	}
}

void Board::move_column()
{
	for (size_t n_col = _columns_count; n_col > 1; --n_col)
	{
		size_t col = n_col - 1;

		if (get_cell(col, _rows_count - 1).get_color() != Color::none)
		{
			continue;
		}

		for (size_t n_row = 0; n_row < _rows_count; ++n_row)
		{
			std::swap(get_cell(col, n_row), get_cell(col - 1, n_row));
		}
	}
}

size_t Board::select_cells(size_t column_index, size_t row_index)
{
	bool selected = true;
	Color color_selected;
	size_t selected_cells = 0;

	size_t selected_cell_position = (column_index + row_index * get_rows_count());
	color_selected = _cells[selected_cell_position].get_color();

	if (_cells[selected_cell_position].is_selected() || color_selected == Color::none)
	{
		return 0;
	}
	_cells[selected_cell_position].set_selected(selected);

	selected_cells += 1;

	if (column_index > 0 && _cells[selected_cell_position - 1].get_color() == color_selected)
	{
		selected_cells += select_cells((column_index - 1), row_index);
	}
	if (column_index < get_columns_count() - 1 && _cells[selected_cell_position + 1].get_color() == color_selected)
	{
		selected_cells += select_cells((column_index + 1), row_index);
	}
	if (row_index > 0 && _cells[selected_cell_position - _rows_count].get_color() == color_selected)
	{
		selected_cells += select_cells(column_index, (row_index - 1));
	}
	if (row_index < get_rows_count() - 1 && _cells[selected_cell_position + _rows_count].get_color() == color_selected)
	{
		selected_cells += select_cells(column_index, (row_index + 1));
	}
	return selected_cells;
}

void Board::deselect_cells() noexcept
{
	for (auto& cell : _cells)
	{
		cell.set_selected(false);
	}
}

void Board::pop_selected_cells()
{
	for (auto& cell : _cells)
	{
		if (cell.is_selected())
		{
			cell = Cell();
		}
	}
}