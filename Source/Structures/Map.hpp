#pragma once
#include "Structures/Room.hpp"
#include <utility> // std::make_pair
#include <unordered_map>
#include "Structures/MapPoint.hpp"


struct Map
{
  // Constructors.
  Map();
  Map(size_t w, size_t h, const ID_Map &id, const Room &startRoom);

  // Public member functions
  std::pair<Tile *, Room *> GetTileAt(MapPoint point);
  void AddRoomRandomly(const Room &toUse);

  // Public member variables
  std::vector<std::pair<Room *, MapPoint>> Rooms; // The rooms, stored in a vector as pairs.
  MapPoint PlayerLoc;                             // The player location in the map according to the map.
  ID_Map ID;                                      // The identifier for the map: The name of it.

private:
  // Private member functions
  void pushRoom(Room *room, MapPoint m);

  // Private member variables
  // Hashtable because this really has no defined size
  std::unordered_map<MapPoint, std::pair<Tile *, Room *>, MapPointHash> _roomsByPoint; // Internal tracking
};
