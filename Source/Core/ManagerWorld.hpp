#pragma once
#include "Core/ManagerBase.hpp"
#include "Structures/Typedefs.hpp"


class ManagerWorld : public ManagerBase
{
public:
  void Init() { DEBUG_PRINT(__FUNCDNAME__); }
  void Update(UpdateInfo i) { DEBUG_PRINT(__FUNCDNAME__); }
  void Shutdown() { DEBUG_PRINT(__FUNCDNAME__); }
};
