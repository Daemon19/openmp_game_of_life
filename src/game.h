#pragma once
#include <SDL.h>

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
  bool running_ = true;

  SDL_Window *window_ = nullptr;
  SDL_Renderer *renderer_ = nullptr;

  Grid grid;
};
