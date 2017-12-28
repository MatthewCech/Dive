#pragma once
#include <unordered_map>
#include "Structures/Typedefs.hpp"

class Entity;

struct Tile
{
  std::unordered_map<ID, Entity> TileContents;
};