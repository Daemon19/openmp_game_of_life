#pragma once
#include <SDL.h>

#include <cstdlib>
#include <ctime>
#include <vector>

class Grid {
 public:
  Grid() = default;

  Grid(int cell_size, int rows, int cols)
      : cell_size_(cell_size), grid_(rows, std::vector<bool>(cols, false)) {
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
  int CountNeighbours_(int row, int col) const;
  static bool ShouldLive_(bool live, int num_neighbours);

 private:
  int cell_size_;
  std::vector<std::vector<bool>> grid_;
};
