#pragma once
#include "Structures/Room.hpp"
#include <utility> // std::make_pair
#include <unordered_map>
#include "Structures/MapPoint.hpp"


struct Map
{
  // Constructor
  Map() : Rooms(), PlayerLoc(), ID("") {  }

  // invoke copy constructor for rooms explicitly.
  Map(size_t w, size_t h, const ID_Map &id, Room startRoom)
    : Rooms()
    , PlayerLoc()
    , ID(id)
  {
    size_t width_offset = startRoom.GetWidth() / 2;
    size_t height_offset = startRoom.GetHeight() / 2;

    Rooms.push_back(std::make_pair(startRoom, MapPoint(PlayerLoc.X - width_offset, PlayerLoc.Y - height_offset)));
  }

  // Get a tile at a specific location.
  Tile *getTileAt(MapPoint point)
  {
    for (auto &pair : Rooms)
    {
      // See if we can skip this room
      if (point.X < pair.second.X)
        continue;
      if (point.Y < pair.second.Y)
        continue;
      if (pair.second.X + pair.first.GetWidth() < point.X)
        continue;
      if (pair.second.Y + pair.first.GetHeight() < point.Y)
        continue;

      return &(pair.first.Tiles[point.X - pair.second.X][point.Y - pair.second.Y]);
    }

    return nullptr;
  }
  // Public member variables
  std::vector<std::pair<Room, MapPoint>> Rooms;
  MapPoint PlayerLoc;
  ID_Map ID;
};
