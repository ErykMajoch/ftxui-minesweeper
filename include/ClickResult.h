#pragma once

#include <variant>

struct Mine {};
struct NoMine {
  NoMine(int n) : number(n) {}
  int number;
};

using ClickResult = std::variant<Mine, NoMine>;
