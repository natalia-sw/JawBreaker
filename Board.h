#pragma once

#include <cstddef>
#include <vector>

#include "Cell.h"

class Board
{
public:
	using cells_t = std::vector<Cell>;

	Board(size_t columns_count, size_t rows_count);

	Cell& get_cell(size_t column_index, size_t row_index) noexcept;
	void collapse_column();
	void move_column();
	size_t select_cells(size_t x, size_t y);
	void deselect_cells() noexcept;
	void pop_selected_cells();
	constexpr const cells_t& get_cells() const& noexcept;
	constexpr size_t get_columns_count() const noexcept;
	constexpr size_t get_rows_count() const noexcept;

private:
	cells_t _cells;
	size_t _columns_count;
	size_t _rows_count;
};

constexpr const Board::cells_t& Board::get_cells() const& noexcept
{
	return _cells;
}

constexpr size_t Board::get_columns_count() const noexcept
{
	return _columns_count;
}

constexpr size_t Board::get_rows_count() const noexcept
{
	return _rows_count;
}
