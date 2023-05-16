#include "Cursor.h"


void Cursor::set_x(int x)
{
	_x = x;
}

void Cursor::set_y(int y)
{
	_y = y;
}

int Cursor::get_x() const
{
	return _x;
}
int Cursor::get_y() const
{
	return _y;
}

void Cursor::move_left()
{
	_x -= 1;
}
void Cursor::move_right()
{
	_x += 1;
}
void Cursor::move_up()
{
	_y -= 1;
}
void Cursor::move_down()
{
	_y += 1;
}