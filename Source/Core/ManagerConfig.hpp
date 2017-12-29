#pragma once
#include "Core/ManagerBase.hpp"

class ManagerConfig : public ManagerBase
{
public:
  void Init();
  void Update(UpdateInfo i) { DEBUG_PRINT(__FUNCDNAME__); }
  void Shutdown() { DEBUG_PRINT(__FUNCDNAME__); }
};
