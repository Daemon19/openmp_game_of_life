#include "game.h"

#include <SDL.h>

#include <iostream>

int Game::Init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Unable to initialize SDL: " << SDL_GetError() << "\n";
    return 1;
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
  if (window_ != nullptr) {
    SDL_DestroyWindow(window_);
  }

  if (renderer_ != nullptr) {
    SDL_DestroyRenderer(renderer_);
  }

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
  SDL_RenderPresent(renderer_);
}
