#pragma once

#include "Game.h"


class IGameInterface
{
public:
	IGameInterface(Game& game) noexcept;
	virtual ~IGameInterface() = default;

	virtual void compute_game_logic() = 0;
	virtual void print_game() = 0;

protected:
	Game& _game;
};