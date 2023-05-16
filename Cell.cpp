#include "Cell.h"


Cell::Cell(Color color) : _color{ color }
{
}

Color Cell::get_color() const
{
	return _color;
}
bool Cell::is_selected() const
{
	return _selected;
}

void Cell::set_selected(bool selected)
{
	_selected = selected;
}