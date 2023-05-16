#pragma once

class Cursor
{
public:

	void set_x(int x);
	void set_y(int y);
	int get_x() const;
	int get_y() const;

	void move_left();
	void move_right();
	void move_up();
	void move_down();

private:
	int _x{};
	int _y{};
};