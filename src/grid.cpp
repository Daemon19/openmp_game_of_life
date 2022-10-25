#include "grid.h"

#include <SDL.h>
#include <omp.h>

void Grid::Update() {
  const Grid prev_grid = *this;

  int r;
#pragma omp parallel for
  for (r = 0; r < Rows(); r++) {
    for (size_t c = 0; c < Cols(); c++) {
      int num_neighbours = prev_grid.CountNeighbours_(r, c);
      grid_[r][c] = Grid::ShouldLive_(prev_grid.grid_[r][c], num_neighbours);
    }
  }
}

void Grid::Render(SDL_Renderer* renderer) const {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  for (size_t r = 0; r < Rows(); r++) {
    for (size_t c = 0; c < Cols(); c++) {
      if (!grid_[r][c]) {
        continue;
      }

      SDL_Rect rect{c * cell_size_, r * cell_size_, cell_size_, cell_size_};
      SDL_RenderFillRect(renderer, &rect);
    }
  }
}

int Grid::CountNeighbours_(int row, int col) const {
  int num_neighbours = 0;

  for (int roff = -1; roff < 2; roff++) {
    int curr_row = row + roff;

    if (curr_row < 0 || curr_row >= Rows()) {
      continue;
    }

    for (int coff = -1; coff < 2; coff++) {
      int curr_col = col + coff;

      if (curr_col < 0 || curr_col >= Cols() || (roff == 0 && coff == 0) ||
          !grid_[curr_row][curr_col]) {
        continue;
      }

      num_neighbours++;
    }
  }

  return num_neighbours;
}

bool Grid::ShouldLive_(bool live, int num_neighbours) {
  if (live && (num_neighbours == 2 || num_neighbours == 3)) {
    return true;
  }

  if (!live && num_neighbours == 3) {
    return true;
  }

  return false;
}
