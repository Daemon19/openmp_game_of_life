#include <SDL.h>

#include <iostream>

#include "game.h"

int main(int argc, char* argv[]) {
  Game game("OpenMP Game of Life", 960, 540);

  if (game.Init() != 0) {
    return 1;
  }

  return 0;
}
