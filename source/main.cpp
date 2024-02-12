#include "../include/board.h"

#include <algorithm>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/canvas.hpp>
#include <memory>
#include <utility>

int main() {
  using namespace ftxui;

  const int WIDTH = 9;
  const int HEIGHT = 9;
  const int MINES = 10;

  // Create a Minesweeper board.
  Board board(HEIGHT, WIDTH, MINES);

  int x_highlight = 0;
  int y_highlight = 0;

  auto c = Canvas(WIDTH * 2, HEIGHT * 4);
  // c.DrawText(0, 0, "⚑", [](Pixel& p) {
    // p.foreground_color = Color::Red;
  // });
  //

  auto renderer = Renderer([&](){
    for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      std::string cell = board.get_cell(i, j);
      c.DrawText(j * 2, i * 4, (cell == "0" ? " " : cell), [&](Pixel& p){

        if (cell == "0") {
            p.background_color = Color::GrayDark;
        }

        Color temp = p.background_color;
        // Highlighted cell
        if (i == y_highlight && j == x_highlight) {
          p.background_color = Color::GrayLight;
        } else {
            p.background_color = temp;
          }

        p.bold = true;
      });
    }
  }
    return canvas(&c) | border;
  });

  renderer |= CatchEvent([&](Event event){
    if (event == Event::ArrowRight) {
      x_highlight = std::min(WIDTH - 1, x_highlight + 1);
    } else if (event == Event::ArrowLeft) {
      x_highlight = std::max(0, x_highlight - 1);
    } else if (event == Event::ArrowUp) {
      y_highlight = std::max(0, y_highlight - 1);
    } else if (event == Event::ArrowDown) {
      y_highlight = std::min(HEIGHT - 1, y_highlight + 1); 
    } else if (event == Event::Character('f')) {
      Position pos = std::make_pair(y_highlight, x_highlight);
      board.flag_cell(pos);
    } else if (event == Event::Return) {
      board.click_cell(std::make_pair(y_highlight, x_highlight));
    }
    return true;
  });

  auto screen = ScreenInteractive::FitComponent();
  screen.Loop(renderer);
  return 0;

}
