#include "Core/ManagerLevel.hpp"
#include <string>
#include "Core/Alert.hpp"
#include "Core/Engine.hpp"
#include "Core/ManagerWorld.hpp"
#include "Core/ManagerConfig.hpp"
#include "Structures/Typedefs.hpp"

void ManagerLevel::Init()
{
  const std::string &start_map = Engine::Instance->Get<ManagerConfig>()->GetValueAsString(KEY_GENERAL_START_MAP);
  _maps.push_back(Engine::Instance->Get<ManagerWorld>()->GetMap(start_map));
  _currentMap = 0;
}

void ManagerLevel::AddMap(const Map &rhs)
{
  _maps.push_back(rhs);
}

Map & ManagerLevel::GetCurrentMap()
{
  if (_currentMap >= _maps.size())
  {
    AlertMessage("You are trying to access a map at index " + std::to_string(_currentMap) + "\n in maps, which is out of bounds!\nAttempt to continue?");
    return _maps.back();
  }
  else
    return _maps[_currentMap];
}