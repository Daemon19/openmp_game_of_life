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
  void HandleEvents();

  bool Running() const { return running_; }

public:
  const std::string kWindowTitle;
  const int kWindowW;
  const int kWindowH;

 private:
  bool running_ = true;

  SDL_Window *window_ = nullptr;
  SDL_Renderer *renderer_ = nullptr;
};
