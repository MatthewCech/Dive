#pragma once
#include "Core/ManagerBase.hpp"



class ManagerWorld : public ManagerBase
{
public:
  void Init();
  void Update(UpdateInfo i) { DEBUG_PRINT(__FUNCDNAME__); }
  void Shutdown() { DEBUG_PRINT(__FUNCDNAME__); }
};
