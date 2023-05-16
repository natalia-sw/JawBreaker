#include "IGameInterface.h"

#include "Game.h"


IGameInterface::IGameInterface(Game& game) noexcept : _game{game}
{
}
