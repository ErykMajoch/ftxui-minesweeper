#include "../include/board.h"
#include <algorithm>
#include <set>
#include <string>
#include <utility>

// Board Constructor
Board::Board(int _rows, int _columns, int _mines) {
    m_rows = _rows;
    m_columns = _columns;
  
    while (m_mines.size() < _mines) {
      m_mines.insert(std::make_pair(random_range(0, m_rows), random_range(0, m_columns)));
    }

}

// Simulated a click on a cell
std::optional<ClickResult> Board::click_cell(Position pos) {
  
  // Check if the cell is already open
  if (m_open.find(pos) != m_open.end()) {
    return{};
  }
  m_open.insert(pos);

  // If the cell clicked is a mine, game over :(
  if (m_mines.find(pos) != m_mines.end()) {
    return Mine();
  }
  // If the cell isn't a mine
  else {
    int count = mine_count(pos);
    if (count == 0) {
      for (const Position neighbour : get_neighbours(pos)) {
        click_cell(neighbour);
      }
    }
    return NoMine(count);
  }

}

// Toggle flagging a cell
void Board::flag_cell(Position pos) {
  if (m_open.find(pos) != m_open.end()) {
    return;
  }
  auto iterator = m_flagged.find(pos);
  if (iterator != m_flagged.end()) {
    m_flagged.erase(iterator);
  } else {
    m_flagged.insert(pos);
  }
}

void Board::reset_board() {
    int mine_number = m_mines.size();
    m_mines = {};
    m_open = {};
    m_flagged = {};
    while (m_mines.size() < mine_number) {
        m_mines.insert(std::make_pair(random_range(0, m_rows), random_range(0, m_columns)));
    }
}

// Get the number of flags
int Board::flag_count() {
    return m_flagged.size();
}

// Get the cell of pos (x,y)
char Board::get_cell(int height, int width) {
  Position pos = std::make_pair(height, width);

  if (m_open.find(pos) == m_open.end()) {
    if (m_flagged.find(pos) != m_flagged.end()) {
      return 'f';
    } else {
      return ' ';
    }
  } else if (m_mines.find(pos) != m_mines.end()) {
    return 'b';
  } else {
    return std::to_string(mine_count(pos))[0];
  }
}

bool Board::game_won() {
    std::set<Position> inter = {};
    for (auto val : m_flagged) {
        if (m_mines.find(val) != m_mines.end()) {
            inter.insert(val);
        }
    }
    return inter.size() == m_mines.size();
}


// ===================
// = Private Methods =
// ===================

// Function for getting the surrounding cells of a given Position
std::set<Position> Board::get_neighbours(Position pos) {
  std::set<Position> neighbours = {};
  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      int row = std::clamp(pos.first + dx, 0, m_rows);
      int column = std::clamp(pos.second + dy, 0, m_columns);
      neighbours.insert(std::make_pair(row, column));
    }
  }
  return neighbours; 
}

// Function for finding the amount of mines in the neighbouring cells
int Board::mine_count(Position pos) {
  int count = 0;
  for (const Position neighbour : get_neighbours(pos)) {
    if (m_mines.find(neighbour) != m_mines.end()) {
      count += 1;
    }
  }
  return count;
}


// Function for generating random numbers in a given range [min,max]
int Board::random_range(int min, int max) {
  std::random_device random_device;
  std::default_random_engine engine(random_device());
  std::uniform_int_distribution<int> distribution(min, max - 1);
  return distribution(engine);
}
