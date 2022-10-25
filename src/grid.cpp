#include "grid.h"

void Grid::Render(SDL_Renderer* renderer) const {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  for (size_t r = 0; r < Rows(); r++) {
    for (size_t c = 0; c < Cols(); c++) {
      if (!grid_[r][c]) {
        continue;
      }

      SDL_Rect rect{c * kCellSize, r * kCellSize, kCellSize, kCellSize};
      SDL_RenderFillRect(renderer, &rect);
    }
  }
}
