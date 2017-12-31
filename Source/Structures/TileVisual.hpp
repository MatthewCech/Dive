#pragma once
#include <string>
#include "Graphics/console-utils.hpp"

struct TileVisual
{
  TileVisual() : ASCII(' '), ImagePath(""), ASCIIColor(RConsole::BLACK) { }

  char ASCII;
  RConsole::Color ASCIIColor;
  std::string ImagePath;
};
