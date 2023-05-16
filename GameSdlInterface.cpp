#include "GameSdlInterface.h"

#include <format>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>


GameSdlInterface::GameSdlInterface(Game& game) : IGameInterface(game)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    _window = SDL_CreateWindow("JawBreaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _window_width, _window_height, SDL_WINDOW_SHOWN);
    if (_window == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == nullptr)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    _font = TTF_OpenFont("ChunkFive.otf", 20);
}

GameSdlInterface::~GameSdlInterface()
{
    TTF_CloseFont(_font);
    _font = nullptr;
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    TTF_Quit();
    SDL_Quit();
}

void GameSdlInterface::compute_game_logic()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            _game.set_quit(true);
        }

        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (y < _game.get_board().get_rows_count() * _cell_height)
            {
                _game.select_cell(x / _cell_width, y / _cell_width);
            }
        }
    }
}

void GameSdlInterface::print_game()
{
    SDL_RenderClear(_renderer);

    SDL_Color none{ 0x00, 0x00, 0x00, 0x00 };
    SDL_Color blue{ 0x00, 0x00, 0xFF, 0xFF };
    SDL_Color black{ 0x00, 0x00, 0x00, 0xFF };
    SDL_Color green{ 0x00, 0xFF, 0x00, 0xFF };
    SDL_Color magenta{ 0xFF, 0x00, 0xFF, 0xFF };
    SDL_Color red{ 0xFF, 0x00, 0x00, 0xFF };
    SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
    SDL_Color yellow{ 0xFF, 0xFF, 0x00, 0xFF };

    for (size_t column_index = 0; column_index <= _game.get_board().get_columns_count()-1; ++column_index)
    {
        for (size_t row_index = 0; row_index <= _game.get_board().get_rows_count() - 1; ++row_index)
        {
            SDL_Rect cell;
            cell.x = column_index * _cell_width;
            cell.y = row_index * _cell_height;
            cell.w = _cell_width;
            cell.h = _cell_height;

            size_t cell_pos = column_index + row_index * _game.get_board().get_rows_count();

            if (_game.get_board().get_cells()[cell_pos].get_color() == Color::none)
            {
                SDL_SetRenderDrawColor(_renderer, none.r, none.g, none.b, none.a);
                SDL_RenderFillRect(_renderer, &cell);
            }
            if (_game.get_board().get_cells()[cell_pos].get_color() == Color::blue)
            {
                SDL_SetRenderDrawColor(_renderer, blue.r, blue.g, blue.b, blue.a);
                SDL_RenderFillRect(_renderer, &cell);

            }
            if (_game.get_board().get_cells()[cell_pos].get_color() == Color::green)
            {
                SDL_SetRenderDrawColor(_renderer, green.r, green.g, green.b, green.a);
                SDL_RenderFillRect(_renderer, &cell);

            }
            if (_game.get_board().get_cells()[cell_pos].get_color() == Color::magenta)
            {
                SDL_SetRenderDrawColor(_renderer, magenta.r, magenta.g, magenta.b, magenta.a);
                SDL_RenderFillRect(_renderer, &cell);

            }
            if (_game.get_board().get_cells()[cell_pos].get_color() == Color::red)
            {
                SDL_SetRenderDrawColor(_renderer, red.r, red.g, red.b, red.a);
                SDL_RenderFillRect(_renderer, &cell);

            }
            if (_game.get_board().get_cells()[cell_pos].get_color() == Color::yellow)
            {
                SDL_SetRenderDrawColor(_renderer, yellow.r, yellow.g, yellow.b, yellow.a);
                SDL_RenderFillRect(_renderer, &cell);

            }
            if (_game.get_board().get_cells()[cell_pos].is_selected())
            {
                SDL_SetRenderDrawColor(_renderer, white.r, white.g, white.b, white.a);
                SDL_RenderDrawRect(_renderer, &cell);
            }
            else
            {
                SDL_SetRenderDrawColor(_renderer, black.r, black.g, black.b, black.a);
                SDL_RenderDrawRect(_renderer, &cell);
            }
        }
    }

    std::stringstream total_score;
    std::stringstream block_score;
    
    total_score << "Total score: " << _game.get_score().total_score;
    block_score << "Block score: " << _game.get_score().block_score;

    SDL_Surface* surface_message1 = TTF_RenderText_Solid(_font, total_score.str().c_str(), white);
    SDL_Surface* surface_message2 = TTF_RenderText_Solid(_font, block_score.str().c_str(), white);

    SDL_Texture* message1 = SDL_CreateTextureFromSurface(_renderer, surface_message1);
    SDL_Texture* message2 = SDL_CreateTextureFromSurface(_renderer, surface_message2);

    SDL_Rect message_rect1;
    message_rect1.x = _window_width/3;
    message_rect1.y = 450;
    message_rect1.w = surface_message1->w;
    message_rect1.h = surface_message1->h;

    SDL_Rect message_rect2;
    message_rect2.x = _window_width / 3;
    message_rect2.y = 450 + surface_message1->h;
    message_rect2.w = surface_message2->w;
    message_rect2.h = surface_message2->h;

    SDL_RenderCopy(_renderer, message1, nullptr, &message_rect1);
    SDL_RenderCopy(_renderer, message2, nullptr, &message_rect2);

    if (_game.is_over())
    {
        SDL_Surface* surface_over_message = TTF_RenderText_Solid(_font, "!!GAME OVER!!", red);
        SDL_Texture* over_message = SDL_CreateTextureFromSurface(_renderer, surface_over_message);

        SDL_Rect over_rect;
        over_rect.x = _window_width / 3;
        over_rect.y = 450 + surface_message1->h + surface_message2->h;
        over_rect.w = surface_over_message->w;
        over_rect.h = surface_over_message->h;
        SDL_RenderCopy(_renderer, over_message, nullptr, &over_rect);

        SDL_DestroyTexture(over_message);
        SDL_FreeSurface(surface_over_message);
    }

    SDL_RenderPresent(_renderer);

    SDL_DestroyTexture(message1);
    SDL_DestroyTexture(message2);
    SDL_FreeSurface(surface_message1);
    SDL_FreeSurface(surface_message2);
    surface_message1 = nullptr;
    surface_message2 = nullptr;
}