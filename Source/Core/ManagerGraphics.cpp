#include "Core/ManagerGraphics.hpp"
#include "Graphics/console-utils.hpp"
#include "Core/ManagerLevel.hpp"
#include "Core/Engine.hpp"



void ManagerGraphics::Init()
{
  RConsole::Canvas::SetCursorVisible(false);
  _width = WIDTH_FUNC;
  _height = HEIGHT_FUNC;
}


void ManagerGraphics::Update(UpdateInfo i)
{
  const Map& map = Engine::Instance->Get<ManagerLevel>()->GetCurrentMap();
  size_t width = WIDTH_FUNC;
  size_t height = HEIGHT_FUNC;
  if (width != _width || height != _height)
  {
    RConsole::Canvas::ReInit(width, height);
    _width = width;
    _height = height;
    RConsole::Canvas::fullClear();
    RConsole::Canvas::SetCursorVisible(false);
  }

  for (const std::pair<Room, MapOffset> &r : map.Rooms)
  {
    int startPosX = (width/2) + r.second.X - map.PlayerLoc.X;
    int startPosY = (height/2) + r.second.Y - map.PlayerLoc.Y;

    for (size_t i = 0; i < r.first.GetWidth(); ++i)
      for (size_t j = 0; j < r.first.GetHeight(); ++j)
        RConsole::Canvas::Draw(r.first.Tiles[i][j].Visual.ASCII, static_cast<float>(startPosX + i), static_cast<float>(startPosY + j), RConsole::WHITE);

  }
  RConsole::Canvas::Draw('@', static_cast<float>(width/2), static_cast<float>(height/2), RConsole::WHITE);
  RConsole::Canvas::Update();
}

