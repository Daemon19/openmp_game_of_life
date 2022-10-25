#pragma once

#include <SDL.h>

#include <string>
#include <string_view>

class Game {
 public:
  Game(std::string_view title, int width, int height)
      : kWindowTitle(title), kWindowW(width), kWindowH(height) {}
  ~Game();

  int Init();

public:
  const std::string kWindowTitle;
  const int kWindowW;
  const int kWindowH;

 private:
  SDL_Window *window_ = nullptr;
  SDL_Renderer *renderer_ = nullptr;
};
