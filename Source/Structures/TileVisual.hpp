#pragma once
#include <string>


struct TileVisual
{
  TileVisual() : ASCII(' '), ImagePath("") { }

  char ASCII;
  std::string ImagePath;
};
