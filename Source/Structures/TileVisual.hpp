#pragma once
#include <string>


struct TileVisual
{
  TileVisual() : ASCII(0), ImagePath("") { }

  char ASCII;
  std::string ImagePath;
};
