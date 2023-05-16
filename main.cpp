#include <memory>

#include "Game.h"
#include "GameSdlInterface.h"
#include "GameTextInterface.h"
#include "IGameInterface.h"


Game make_new_game()
{
	return Game{11, 11};
}

int main(int argc, char* argv[])
{
	auto game{make_new_game()};

	std::unique_ptr<IGameInterface> game_interface{std::make_unique<GameSdlInterface>(game)};
	// std::unique_ptr<IGameInterface> game_interface = std::make_unique<GameTextInterface>(game);

	do
	{
		game_interface->print_game();
		game_interface->compute_game_logic();

		if (game.get_reset())
		{
			game = make_new_game();
		}
	}
	while (!game.get_quit());

	return 0;
}
