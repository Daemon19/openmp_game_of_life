#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>
#include <string_view>

#include "grid.h"

class Game {
 public:
  Game(std::string_view title) : window_title_(title) {}
  ~Game();

  int Init();
  void HandleEvents();
  void Update();
  void Render() const;

  bool Running() const { return running_; }

 private:
  int GetFps_() const {
    static Uint32 last_ticks = 0;
    Uint32 elapsed = SDL_GetTicks() - last_ticks;
    float fps = (elapsed > 0) ? 1000.0f / elapsed : 0.0f;
    last_ticks = SDL_GetTicks();
    return static_cast<int>(fps);
  }

 private:
  int window_w_;
  int window_h_;
  std::string window_title_;

  bool running_ = true;

  SDL_Window *window_ = nullptr;
  SDL_Renderer *renderer_ = nullptr;

  Grid grid;

  TTF_Font *font_ = nullptr;
};
