#pragma once
#include <unordered_map>
#include "Structures/Typedefs.hpp"
#include "Structures/TileVisual.hpp"

class Entity;

struct Tile
{
  TileVisual Visual;
  std::unordered_map<ID, Entity> TileContents;
};