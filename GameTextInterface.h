#pragma once

#include "Cursor.h"
#include "Game.h"
#include "IGameInterface.h"

class GameTextInterface : public IGameInterface
{
public:
	GameTextInterface(Game& game);
	virtual void compute_game_logic() override;
	virtual void print_game() override;

private:
	Cursor _cursor;
};