#include <SDL.h>

#include <iostream>

#include "game.h"

int main(int argc, char* argv[]) {
  Game game("OpenMP Game of Life");

  if (game.Init() != 0) {
    return 1;
  }

  while (game.Running()) {
    game.HandleEvents();
    game.Update();
    game.Render();
  }

  return 0;
}
