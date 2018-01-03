#include "Structures/Map.hpp"
#include <random>



// Constructor
Map::Map() 
  : Rooms()
  , PlayerLoc()
  , ID("")
  , _roomsByPoint()
{  }


// invoke copy constructor for rooms explicitly.
Map::Map(size_t w, size_t h, const ID_Map &id, const Room &startRoom)
  : Rooms()
  , PlayerLoc()
  , ID(id)
  , _roomsByPoint()
{
  Room *room = new Room(startRoom);
  size_t width_offset = room->GetWidth() / 2;
  size_t height_offset = room->GetHeight() / 2;
  room->Visited = true;
  pushRoom(room, MapPoint(PlayerLoc.X - width_offset, PlayerLoc.Y - height_offset));
}


// Get a tile and room it's in at a specific location.
std::pair<Tile *, Room *> Map::GetTileAt(MapPoint point)
{
  auto iter = _roomsByPoint.find(point);
  
  if (iter == _roomsByPoint.end())
    return { nullptr, nullptr };

  return iter->second;

  // ORIGINAL IMPLEMENTATION
  //for (auto &pair : Rooms)
  //{
  //  // See if we can skip this room
  //  if (point.X < pair.second.X)
  //    continue;
  //  if (point.Y < pair.second.Y)
  //    continue;
  //  if (pair.second.X + static_cast<int>(pair.first->GetWidth()) <= point.X)
  //    continue;
  //  if (pair.second.Y + static_cast<int>(pair.first->GetHeight()) <= point.Y)
  //    continue;

  //  return std::make_pair(&(pair.first->Tiles[point.X - pair.second.X][point.Y - pair.second.Y]), pair.first);
  //}

  //return std::make_pair(nullptr, nullptr);
}



// Add a room object when applicable
// Intentionally invoke copy constructor
void Map::AddRoomRandomly(const Room &toUse)
{
  Room *toAdd = new Room(toUse);
  MapPoint newOffset(0, 0);
  const int addWidth = toAdd->GetWidth();
  const int addHeight = toAdd->GetHeight();

  for (size_t i = 0; i < Rooms.size(); ++i)
  {
    // Make it easier to use the room object
    const Room &room = *Rooms[i].first;
    const MapPoint &mp = Rooms[i].second;
    const int roomWidth = room.GetWidth();
    const int roomHeight = room.GetHeight();

    // Sides for new 
    const int xminN = newOffset.X;
    const int xmaxN = newOffset.X + addWidth;
    const int yminN = newOffset.Y;
    const int ymaxN = newOffset.Y + addHeight;

    // Sides for current room
    const int xminR = mp.X;
    const int xmaxR = mp.X + roomWidth;
    const int yminR = mp.Y;
    const int ymaxR = mp.Y + roomHeight;

    // If the two rooms are not overlapping, continue.
    if (xmaxN < xminR || xminN > xmaxR)
      continue;
    if (ymaxN < yminR || yminN > ymaxR)
      continue;
    
    // Reset a few things and them prepare to move the room.
    i = -1;
    int dir = rand() % 4;
    const int xOffset = addWidth / 2 + (rand() % 3);
    const int yOffset = addHeight / 2 + (rand() % 3);

    switch (dir)
    {
    case 0:
      newOffset.X -= xOffset;
      newOffset.Y -= yOffset;
      break;
    case 1:
      newOffset.X += xOffset;
      newOffset.Y -= yOffset;
      break;
    case 2:
      newOffset.X -= xOffset;
      newOffset.Y += yOffset;
      break;
    case 3:
      newOffset.X += xOffset;
      newOffset.Y += yOffset;
      break;
    }
  }

  pushRoom(toAdd, newOffset);
}


// Push a room to the back
void Map::pushRoom(Room *room, MapPoint m)
{
  Rooms.push_back(std::make_pair(room, m));
  
  for(size_t x = 0; x < room->Tiles.size(); ++x)
    for (size_t y = 0; y < room->Tiles[x].size(); ++y)
      _roomsByPoint[MapPoint(m.X + x, m.Y + y)] = std::make_pair(&(room->Tiles[x][y]), room);
}
