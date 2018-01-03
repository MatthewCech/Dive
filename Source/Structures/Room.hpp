#pragma once
#include "Structures/Tile.hpp"
#include "Structures/Typedefs.hpp"
#include "Structures/MapPoint.hpp"



// A room is a collection of tiles and an ID.
// Tiles are stored as [x][y]!!
// Note: 0,0 is in the upper left!
struct Room
{
  Room(size_t w, size_t h, const ID_Room &id)
    : Tiles(w, std::vector<Tile>(h))
    , ID(id)
    , Visited(true)//, Visited(false)
  {  }

  Room()
    : Tiles(0, std::vector<Tile>(0))
    , ID()
    , Visited(true)//, Visited(false)
  {  }

  size_t GetHeight() const
  {
    if (Tiles.size() > 0)
      return Tiles[0].size();

    return 0;
  }

  size_t GetWidth() const
  {
    return Tiles.size();
  }

  std::vector<std::vector<Tile>> Tiles;

  ID_Room ID;
  bool Visited;
};
