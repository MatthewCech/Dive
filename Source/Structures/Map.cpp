#include "Structures/Map.hpp"
#include <random>


// Get a tile at a specific location.
Tile *Map::GetTileAt(MapPoint point)
{
  for (auto &pair : Rooms)
  {
    // See if we can skip this room
    if (point.X < pair.second.X)
      continue;
    if (point.Y < pair.second.Y)
      continue;
    if (pair.second.X + static_cast<int>(pair.first.GetWidth()) <= point.X)
      continue;
    if (pair.second.Y + static_cast<int>(pair.first.GetHeight()) <= point.Y)
      continue;

    return &(pair.first.Tiles[point.X - pair.second.X][point.Y - pair.second.Y]);
  }

  return nullptr;
}



// Add a room object when applicable
// Intentionally invoke copy constructor
void Map::AddRoomRandomly(Room toAdd)
{
  MapPoint newOffset(0, 0);
  const int addWidth = toAdd.GetWidth();
  const int addHeight = toAdd.GetHeight();
  toAdd.Visited = true;

  for (size_t i = 0; i < Rooms.size(); ++i)
  {
    // Make it easier to use the room object
    const Room &room = Rooms[i].first;
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

  Rooms.push_back(std::make_pair(toAdd, newOffset));
}

