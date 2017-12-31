#include "Core/ManagerInput.hpp"
#include <ConsoleInput/console-input.h>
#include "Utils/UtilsString.hpp"
#include "Core/ManagerLevel.hpp"
#include "Core/Engine.hpp"

void ManagerInput::Update(UpdateInfo i) 
{
  if (KeyHit())
  {
    char c = GetChar();
    Map &map = Engine::Instance->Get<ManagerLevel>()->GetCurrentMap();
    switch (tolower(c))
    {
    case 'w': map.PlayerLoc.Y -= 1; break;
    case 'a': map.PlayerLoc.X -= 1; break;
    case 's': map.PlayerLoc.Y += 1; break;
    case 'd': map.PlayerLoc.X += 1; break;
    }
  }
}