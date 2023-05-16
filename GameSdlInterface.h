#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "Game.h"
#include "IGameInterface.h"


class GameSdlInterface : public IGameInterface
{
public:
	GameSdlInterface(Game& game);
	~GameSdlInterface();

	virtual void compute_game_logic() override;
	virtual void print_game() override;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	TTF_Font* _font;
	static const int _window_width = 440;
	static const int _window_height = 540;
	static const int _cell_width = 40;
	static const int _cell_height = 40;
};