#pragma once

#include "Color.h"


class Cell
{
public:
	Cell(Color color = Color::none);
	Color get_color() const;
	bool is_selected() const;
	void set_selected(bool selected);

private:
	Color _color;
	bool _selected = false;
};