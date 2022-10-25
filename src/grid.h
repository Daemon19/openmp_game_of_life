#pragma once
#include <SDL.h>

#include <cstdlib>
#include <ctime>
#include <vector>

class Grid {
 public:
  Grid(int cell_size, int rows, int cols)
      : kCellSize(cell_size), grid_(rows, std::vector<bool>(cols, false)) {
    std::srand(time(nullptr));
    for (size_t r = 0; r < Rows(); r++) {
      for (size_t c = 0; c < Cols(); c++) {
        grid_[r][c] = std::rand() % 2;
      }
    }
  }

  void Update();
  void Render(SDL_Renderer *renderer) const;

  size_t Rows() const { return grid_.size(); }
  size_t Cols() const { return grid_[0].size(); }

 private:
  int CountNeighbours_(int row, int col);
  static bool ShouldLive_(bool live, int num_neighbours);

 private:
  const int kCellSize;

  std::vector<std::vector<bool>> grid_;
};
