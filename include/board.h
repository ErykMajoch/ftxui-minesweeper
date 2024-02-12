#pragma once

#include "ClickResult.h"

#include <iostream>
#include <set>
#include <utility>
#include <vector>
#include <random>
#include <optional>
#include <algorithm>

typedef std::pair<int,int> Position;

class Board {
public:
  Board(int _rows, int _columns, int _mines);

  std::optional<ClickResult> click_cell(Position pos);
  void flag_cell(Position pos);
  void reset_board();
  int flag_count();
  
  char get_cell(int height, int width);
  bool game_won();

private:
    std::set<Position> m_mines = {};
    std::set<Position> m_flagged = {};
    int m_rows = 9;
    int m_columns = 9;
    std::set<Position> m_open = {};

  std::set<Position> get_neighbours(Position pos);
  int mine_count(Position pos);

  // Random number in range [min,max)
  int random_range(int min, int max);
};
