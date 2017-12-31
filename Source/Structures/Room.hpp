#pragma once
#include "Structures/Tile.hpp"
#include "Structures/Typedefs.hpp"


// A room is a collection of tiles and an ID.
// Tiles are stored as [x][y]!!
// Note: 0,0 is in the upper left!
struct Room
{
  Room(size_t w, size_t h, const ID_Room &id)
    : Tiles(w, std::vector<Tile>(h))
    , ID(id)
  {  }

  Room()
    : Tiles(0, std::vector<Tile>(0))
    , ID()
  {  }

  size_t GetHeight() const
  {
    size_t widest = 0;
    for (size_t i = 0; i < Tiles.size(); ++i)
      if (Tiles[i].size() > widest)
        widest = Tiles[i].size();

    return widest;
  }

  size_t GetWidth() const
  {
    return Tiles.size();
  }

  std::vector<std::vector<Tile>> Tiles;
  ID_Room ID;
};
