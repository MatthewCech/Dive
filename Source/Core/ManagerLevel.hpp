#pragma once
#include "Core/ManagerBase.hpp"
#include "Structures/Map.hpp"


class ManagerLevel : public ManagerBase
{
public:
  void Init();
  void Update(UpdateInfo i) { DEBUG_PRINT(__FUNCDNAME__); }
  void AddMap(const Map &rhs);
  Map &GetCurrentMap();

public:
  size_t _currentMap;
  std::vector<Map> _maps;
};
