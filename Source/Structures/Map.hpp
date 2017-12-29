#pragma once
#include "Structures/Room.hpp"
#include <utility> // std::make_pair


struct MapOffset
{
  MapOffset() : X(0), Y(0) { }
  MapOffset(int x, int y) : X(x), Y(y) { }
  int X;
  int Y;
};
struct Map
{
  // invoke copy constructor for rooms explicitly.
  Map(size_t w, size_t h, const ID_Map &id, Room startRoom)
    : Rooms()
    , StartLocation()
    , ID(id)
  {
    size_t width_offset = startRoom.GetWidth() / 2;
    size_t height_offset = startRoom.GetHeight() / 2;

    Rooms.push_back(std::make_pair(startRoom, MapOffset(StartLocation.X - width_offset, StartLocation.Y - height_offset)));
  }

  std::vector<std::pair<Room, MapOffset>> Rooms;
  MapOffset StartLocation;
  ID_Map ID;
};