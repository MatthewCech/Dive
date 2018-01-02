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
    startRoom.Visited = true;
    Rooms.push_back(std::make_pair(startRoom, MapPoint(PlayerLoc.X - width_offset, PlayerLoc.Y - height_offset)));
  }

  // Public member functions
  Tile *GetTileAt(MapPoint point);
  void AddRoomRandomly(Room toAdd);

  // Public member variables
  std::vector<std::pair<Room, MapPoint>> Rooms;
  MapPoint PlayerLoc;
  ID_Map ID;
};
