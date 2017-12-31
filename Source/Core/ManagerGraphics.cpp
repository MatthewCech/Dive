#include "Core/ManagerGraphics.hpp"
#include "Graphics/console-utils.hpp"
#include "Core/ManagerLevel.hpp"
#include "Core/Engine.hpp"
#include "Core/ManagerConfig.hpp"

static RConsole::Color colors[RConsole::PREVIOUS_COLOR];


void ManagerGraphics::Init()
{
  RConsole::Canvas::SetCursorVisible(false);
  _width = WIDTH_FUNC;
  _height = HEIGHT_FUNC;

  colors[RConsole::BLACK] = RConsole::DARKGREY;
  colors[RConsole::BLUE] = RConsole::DARKGREY;
  colors[RConsole::GREEN] = RConsole::DARKGREY;
  colors[RConsole::CYAN] = RConsole::DARKGREY;
  colors[RConsole::RED] = RConsole::DARKGREY;
  colors[RConsole::MAGENTA] = RConsole::DARKGREY;
  colors[RConsole::BROWN] = RConsole::DARKGREY;
  colors[RConsole::GREY] = RConsole::DARKGREY;
  colors[RConsole::DARKGREY] = RConsole::DARKGREY;
  colors[RConsole::LIGHTBLUE] = RConsole::BLUE;
  colors[RConsole::LIGHTGREEN] = RConsole::GREEN;
  colors[RConsole::LIGHTCYAN] = RConsole::CYAN;
  colors[RConsole::LIGHTRED] = RConsole::RED;
  colors[RConsole::LIGHTMAGENTA] = RConsole::MAGENTA;
  colors[RConsole::YELLOW] = RConsole::DARKGREY;
  colors[RConsole::WHITE] = RConsole::GREY;

  RConsole::Canvas::FillCanvas(RConsole::RasterInfo('`', RConsole::DARKGREY));
}


void ManagerGraphics::Update(UpdateInfo i)
{
  // Get map and establish required adjustments.
  const Map& map = Engine::Instance->Get<ManagerLevel>()->GetCurrentMap();
  size_t width = WIDTH_FUNC;
  size_t height = HEIGHT_FUNC;
  if (width != _width || height != _height)
  {
    RConsole::Canvas::ReInit(width, height);
    _width = width;
    _height = height;
    RConsole::Canvas::SetCursorVisible(false);
  }
  RConsole::Canvas::FillCanvas(RConsole::RasterInfo('`', RConsole::DARKGREY));

  // Start by drawing the rooms.
  for (const std::pair<Room, MapOffset> &r : map.Rooms)
  {
    int startPosX = (width/2) + r.second.X - map.PlayerLoc.X;
    int startPosY = (height/2) + r.second.Y - map.PlayerLoc.Y;

    for (size_t i = 0; i < r.first.GetWidth(); ++i)
      for (size_t j = 0; j < r.first.GetHeight(); ++j)
      {
        const TileVisual &t = r.first.Tiles[i][j].Visual;
        RConsole::Canvas::Draw(t.ASCII, static_cast<float>(startPosX + i), static_cast<float>(startPosY + j), t.ASCIIColor);
      }

  }
  RConsole::Canvas::Draw('@', static_cast<float>(width/2), static_cast<float>(height/2), RConsole::WHITE);
  RConsole::Canvas::Update();
}

