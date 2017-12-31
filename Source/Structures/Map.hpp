#pragma once
#include "Structures/Room.hpp"
#include <utility> // std::make_pair
#include <unordered_map>

struct MapOffset
{
  MapOffset() : X(0), Y(0) { }
  MapOffset(int x, int y) : X(x), Y(y) { }
  int X;
  int Y;
};
struct Map
{
  Map() : Rooms(), PlayerLoc(), ID("") {  }

  // invoke copy constructor for rooms explicitly.
  Map(size_t w, size_t h, const ID_Map &id, Room startRoom)
    : Rooms()
    , PlayerLoc()
    , ID(id)
  {
    size_t width_offset = startRoom.GetWidth() / 2;
    size_t height_offset = startRoom.GetHeight() / 2;

    Rooms.push_back(std::make_pair(startRoom, MapOffset(PlayerLoc.X - width_offset, PlayerLoc.Y - height_offset)));
  }

  std::vector<std::pair<Room, MapOffset>> Rooms;
  MapOffset PlayerLoc;
  ID_Map ID;
};