#include "Core/ManagerGraphics.hpp"
#include "Graphics/console-utils.hpp"
#include "Core/ManagerLevel.hpp"
#include "Core/Engine.hpp"
#include "Core/ManagerConfig.hpp"
#include "Structures/Typedefs.hpp"
#include "Structures/TileFlags.hpp"


static RConsole::Color _fadeLookup[RConsole::PREVIOUS_COLOR];

void ManagerGraphics::Init()
{
  RConsole::Canvas::SetCursorVisible(false);
  _width = WIDTH_FUNC;
  _height = HEIGHT_FUNC;

  _fadeLookup[RConsole::BLACK] = RConsole::DARKGREY;
  _fadeLookup[RConsole::BLUE] = RConsole::DARKGREY;
  _fadeLookup[RConsole::GREEN] = RConsole::DARKGREY;
  _fadeLookup[RConsole::CYAN] = RConsole::DARKGREY;
  _fadeLookup[RConsole::RED] = RConsole::DARKGREY;
  _fadeLookup[RConsole::MAGENTA] = RConsole::DARKGREY;
  _fadeLookup[RConsole::BROWN] = RConsole::DARKGREY;
  _fadeLookup[RConsole::GREY] = RConsole::DARKGREY;
  _fadeLookup[RConsole::DARKGREY] = RConsole::DARKGREY;
  _fadeLookup[RConsole::LIGHTBLUE] = RConsole::BLUE;
  _fadeLookup[RConsole::LIGHTGREEN] = RConsole::GREEN;
  _fadeLookup[RConsole::LIGHTCYAN] = RConsole::CYAN;
  _fadeLookup[RConsole::LIGHTRED] = RConsole::RED;
  _fadeLookup[RConsole::LIGHTMAGENTA] = RConsole::MAGENTA;
  _fadeLookup[RConsole::YELLOW] = RConsole::DARKGREY;
  _fadeLookup[RConsole::WHITE] = RConsole::GREY;

  RConsole::Canvas::FillCanvas(RConsole::RasterInfo('`', RConsole::DARKGREY));
  _subWalls = Engine::Instance->Get<ManagerConfig>()->GetValueAsBool(KEY_GENERAL_WALLS_AS_219);
}


void ManagerGraphics::Update(UpdateInfo i)
{
  // Get map and establish required adjustments.
  const Map& map = Engine::Instance->Get<ManagerLevel>()->GetCurrentMap();
  ManagerConfig *conf = Engine::Instance->Get<ManagerConfig>();

  // Establish if resize occurred.
  const size_t width = WIDTH_FUNC;
  const size_t height = HEIGHT_FUNC;
  if (width != _width || height != _height)
  {
    RConsole::Canvas::ReInit(width, height);
    _width = width;
    _height = height;
    RConsole::Canvas::SetCursorVisible(false);
  }

  // Configure for drawing.
  const int halfWidth = width / 2;
  const int halfHeight = height / 2;
  RConsole::Canvas::FillCanvas(RConsole::RasterInfo('`', RConsole::DARKGREY));

  // Start by drawing the rooms.
  for (const std::pair<Room, MapPoint> &r : map.Rooms)
  {
    // Collect some initial values that won't be changing 
    const int startPosX = halfWidth + r.second.X - map.PlayerLoc.X;
    const int startPosY = halfHeight + r.second.Y - map.PlayerLoc.Y;
    const int roomWidth = r.first.GetWidth();
    const int roomHeight = r.first.GetHeight();

    // Determine if we're in the room.
    bool insideRoom = true;
    if (halfWidth >= startPosX + roomWidth || halfWidth < startPosX)
      insideRoom = false;
    else if (halfHeight >= startPosY + roomHeight || halfHeight < startPosY)
      insideRoom = false;

    // Draw the room
    for (int i = 0; i < roomWidth; ++i)
      for (int j = 0; j < roomHeight; ++j)
      {
        // Value collection
        const Tile &tile = r.first.Tiles[i][j];
        const TileVisual &tileVisual = tile.Visual;
        char ascii = tileVisual.ASCII;

        // Handle solid wall coloring
        if ((tile.Flags & TileFlags::WALL) == TileFlags::WALL)
          if (_subWalls)
            ascii = static_cast<unsigned char>(219);

        // Handle fade coloring
        RConsole::Color color = tileVisual.ASCIIColor;
        if (insideRoom == false)
          color = _fadeLookup[color];

        RConsole::Canvas::Draw(ascii, static_cast<float>(startPosX + i), static_cast<float>(startPosY + j), color);
      }

  }

  std::string c = conf->GetValueAsString(KEY_GENERAL_PLAYER_ASCII);
  RConsole::Color color = conf->GetCharAsColor(c[0]);
  RConsole::Canvas::Draw(c[0], static_cast<float>(halfWidth), static_cast<float>(halfHeight), color);
  RConsole::Canvas::Update();
}

