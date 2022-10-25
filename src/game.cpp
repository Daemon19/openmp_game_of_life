#include "game.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>
#include <string>

static void RenderText(SDL_Renderer *renderer, const char *text, TTF_Font *font,
                       SDL_Color color);

int Game::Init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Unable to initialize SDL: " << SDL_GetError() << "\n";
    return 1;
  }

  if (TTF_Init() < 0) {
    std::cerr << "Unable to initialize SDL_ttf: " << TTF_GetError() << "\n";
    return 1;
  }

  font_ = TTF_OpenFont("font/font.ttf", 24);
  if (!font_) {
    std::cerr << "Unable to load font: " << TTF_GetError() << "\n";
  }

  window_ = SDL_CreateWindow(kWindowTitle.c_str(), SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, kWindowW, kWindowH, 0);
  if (window_ == nullptr) {
    std::cerr << "Unable to create a window: " << SDL_GetError() << "\n";
    SDL_Quit();
    return 1;
  }

  renderer_ = SDL_CreateRenderer(
      window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer_ == nullptr) {
    std::cerr << "Unable to create a renderer: " << SDL_GetError() << "\n";
    SDL_DestroyWindow(window_);
    SDL_Quit();
    return 1;
  }

  return 0;
}

Game::~Game() {
  if (font_ != nullptr) {
    TTF_CloseFont(font_);
  }

  if (window_ != nullptr) {
    SDL_DestroyWindow(window_);
  }

  if (renderer_ != nullptr) {
    SDL_DestroyRenderer(renderer_);
  }

  TTF_Quit();
  SDL_Quit();
}

void Game::HandleEvents() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      running_ = false;
    }
  }
}

void Game::Update() { grid.Update(); }

void Game::Render() const {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);
  grid.Render(renderer_);
  std::string fps = std::to_string(GetFps_());
  RenderText(renderer_, fps.c_str(), font_, {255, 0, 0});
  SDL_RenderPresent(renderer_);
}

static void RenderText(SDL_Renderer *renderer, const char *text, TTF_Font *font,
                       SDL_Color color) {
  SDL_Surface *text_surf = TTF_RenderText_Solid(font, text, {0, 255, 0});
  if (text == nullptr) {
    std::cerr << "Failed to render text: " << TTF_GetError() << "\n";
    return;
  }

  SDL_Texture *text_tex = SDL_CreateTextureFromSurface(renderer, text_surf);
  SDL_Rect dest{0, 0, text_surf->w, text_surf->h};
  SDL_RenderCopy(renderer, text_tex, nullptr, &dest);

  SDL_FreeSurface(text_surf);
  SDL_DestroyTexture(text_tex);
}
