#include "Core/ManagerInput.hpp"
#include <ConsoleInput/console-input.h>
#include "Utils/UtilsString.hpp"
#include "Core/ManagerLevel.hpp"
#include "Core/Engine.hpp"
#include "Structures/TileFlags.hpp"



enum DirectionRelative
{
  LEFT,
  RIGHT,
  UP,
  DOWN
};

// Consider caching this!!!
bool canMoveInDir(DirectionRelative dir, Map &map)
{
  // Evaluate movement roles here or in map
  std::pair<Tile *, Room *> tile;
  switch (dir)
  {
  case DirectionRelative::UP:
    tile = map.GetTileAt({ map.PlayerLoc.X, map.PlayerLoc.Y - 1 });
    break;
  case DirectionRelative::LEFT:
    tile = map.GetTileAt({ map.PlayerLoc.X - 1, map.PlayerLoc.Y });
    break;
  case DirectionRelative::DOWN:
    tile = map.GetTileAt({ map.PlayerLoc.X, map.PlayerLoc.Y + 1 });
    break;
  case DirectionRelative::RIGHT:
    tile = map.GetTileAt({ map.PlayerLoc.X + 1, map.PlayerLoc.Y });
    break;
  }

  if (tile.first == nullptr)
    return true;

  tile.second->Visited = true;

  if ((tile.first->Flags & TileFlags::WALL))
    return false;

  return true;
}
void ManagerInput::Update(UpdateInfo i) 
{
  if (KeyHit())
  {
    char c = GetChar();
    Map &map = Engine::Instance->Get<ManagerLevel>()->GetCurrentMap();

    // Evaluate movement roles here or in map
    switch (tolower(c))
    {
    case 'w': 
      if(canMoveInDir(DirectionRelative::UP, map))
        map.PlayerLoc.Y -= 1; 
      break;
    case 'a': 
      if (canMoveInDir(DirectionRelative::LEFT, map))
        map.PlayerLoc.X -= 1; 
      break;
    case 's': 
      if (canMoveInDir(DirectionRelative::DOWN, map))
        map.PlayerLoc.Y += 1; 
      break;
    case 'd': 
      if (canMoveInDir(DirectionRelative::RIGHT, map))
        map.PlayerLoc.X += 1; 
      break;
    }
  }
}