#pragma once
#include "Core/ManagerBase.hpp"
#include "Structures/Typedefs.hpp"
#include "Structures/Room.hpp"
#include "Structures/Map.hpp"
#include <unordered_map>



class ManagerWorld : public ManagerBase
{
public:
  void Init();
  void Update(UpdateInfo i) { DEBUG_PRINT(__FUNCDNAME__); }
  void Shutdown() { DEBUG_PRINT(__FUNCDNAME__); }

private:
  std::unordered_map<ID_Room, Room> _rooms;
  std::unordered_map<ID_Map, Map> _maps;
};
