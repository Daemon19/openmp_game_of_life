#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>
#include <string_view>

#include "grid.h"

class Game {
 public:
  Game(std::string_view title, int width, int height)
      : kWindowTitle(title),
        kWindowW(width),
        kWindowH(height),
        grid(10, height / 10, width / 10) {}
  ~Game();

  int Init();
  void HandleEvents();
  void Update();
  void Render() const;

  bool Running() const { return running_; }

 public:
  const std::string kWindowTitle;
  const int kWindowW;
  const int kWindowH;

 private:
  int GetFps_() const {
    static Uint32 last_ticks = 0;
    Uint32 elapsed = SDL_GetTicks() - last_ticks;
    float fps = (elapsed > 0) ? 1000.0f / elapsed : 0.0f;
    last_ticks = SDL_GetTicks();
    return static_cast<int>(fps);
  }

 private:
  bool running_ = true;

  SDL_Window *window_ = nullptr;
  SDL_Renderer *renderer_ = nullptr;

  Grid grid;

  TTF_Font *font_ = nullptr;
};
