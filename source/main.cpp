#include <cstdlib>
#include <iostream>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <utility>

#include "../include/board.h"

int main() {
  using namespace ftxui;
  Board minesweeper = Board(9, 9, 10);
  while (!minesweeper.has_lost()) {
    minesweeper.display_board();
    int x, y;
    std::cout << "(x) > ";
    std::cin >> x;
    std::cout << "(y) > ";
    std::cin >> y;
    Position pos = std::make_pair(x, y);
    minesweeper.click_cell(pos);
  }
  std::system("clear");
  minesweeper.display_board();
  std::cout << "You lost!";
  return 0;
}
