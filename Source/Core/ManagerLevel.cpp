#include "Core/ManagerLevel.hpp"
#include <string>
#include "Core/Alert.hpp"
#include "Core/Engine.hpp"
#include "Core/ManagerWorld.hpp"

void ManagerLevel::Init()
{
  Engine::Instance->Get<ManagerWorld>();
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