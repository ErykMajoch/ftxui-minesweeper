#include "../include/board.h"

#include <algorithm>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/flexbox_config.hpp>
#include <utility>

int main() {
  using namespace ftxui;

  const int WIDTH = 50;
  const int HEIGHT = 10;
  const int MINES = 80;

  // Create a Minesweeper board.
  Board board = Board(HEIGHT, WIDTH, MINES);

  int x_highlight = 0;
  int y_highlight = 0;

  auto screen = ScreenInteractive::Fullscreen();
auto center = FlexboxConfig()
    .Set(FlexboxConfig::JustifyContent::Center)
    .Set(FlexboxConfig::AlignContent::Center);

  auto c = Canvas(WIDTH * 2, HEIGHT * 4);
  auto renderer = Renderer([&](){
    for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      char cell = board.get_cell(i, j);

      c.DrawText(j * 2, i * 4, std::string(1, (cell == '0' ? ' ' : cell)), [&](Pixel& p){
          switch (cell) {
              case '1': p.foreground_color = Color::Blue; break;
              case '2': p.foreground_color = Color::Green; break;
              case '3': p.foreground_color = Color::Red; break;
              case '4': p.foreground_color = Color::DarkBlue; break;
              case '5': p.foreground_color = Color::RosyBrown; break;
              case '6': p.foreground_color = Color::Aquamarine1; break;
              case '7': p.foreground_color = Color::Black; break;
              case '8': p.foreground_color = Color::GrayLight; break;
              default: p.foreground_color = Color::Default; break;
          }
          if (cell != ' ' && cell != 'f') {
              p.background_color = Color::GrayDark;
          }

//          Implement cursor highlight
            if (i == y_highlight && j == x_highlight && cell != 'b') {
                p.background_color = Color::LightSkyBlue1;
            } else {
                switch (cell) {
                    case 'f': p.background_color = Color::Red; break;
                    case 'b': p.background_color = Color::Black; break;
                    case ' ': p.background_color = Color::Default; break;
                    default: p.background_color = Color::GrayDark; break;
                }
            }
          p.bold = true;
      });

      if (cell == 'b' || board.game_won()) {
         screen.Exit();
      }
    }
  }
  return flexbox({
      vbox({
          ftxui::center(text("Minesweeper")),
          hbox({
            vbox(canvas(&c) | border),
            separator(),
            ftxui::center(vbox({
              window(text("Mines"), ftxui::center(text(std::to_string(MINES)))),
              window(text("Flags"), ftxui::center(text(std::to_string(board.flag_count())))),
            }))
          }),
          ftxui::center(text("Made by Eryk Majoch"))
      }) | border}, center);
  });

  renderer |= CatchEvent([&](const Event& event){
    if (event == Event::ArrowRight) {
      x_highlight = std::min(WIDTH - 1, x_highlight + 1);
    } else if (event == Event::ArrowLeft) {
      x_highlight = std::max(0, x_highlight - 1);
    } else if (event == Event::ArrowUp) {
      y_highlight = std::max(0, y_highlight - 1);
    } else if (event == Event::ArrowDown) {
      y_highlight = std::min(HEIGHT - 1, y_highlight + 1); 
    } else if (event == Event::Character('f')) {
        if (board.flag_count() < MINES) {
            Position pos = std::make_pair(y_highlight, x_highlight);
            board.flag_cell(pos);
        }
    } else if (event == Event::Return) {
      board.click_cell(std::make_pair(y_highlight, x_highlight));
    } else if (event == Event::Character('q')) {
        screen.Exit();
    } else if (event == Event::Character('r')) {
        board.reset_board();
    }
    return true;
  });

  Screen::Cursor cursor;
  cursor.shape = ftxui::Screen::Cursor::Hidden;

  screen.SetCursor(cursor);
  screen.Loop(renderer);

  if (board.game_won()) {
      std::cout << "You won! :D\n";
  } else {
      std::cout << "You lost :(\n";
  }

  return 0;

}
