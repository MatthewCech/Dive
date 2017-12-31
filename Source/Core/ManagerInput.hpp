#pragma once
#include "Core/ManagerBase.hpp"
#include "RUtils/RMacros.hpp"



class ManagerInput : public ManagerBase
{
public:
  void Init() { DEBUG_PRINT(__FUNCDNAME__); }
  void Update(UpdateInfo i) { DEBUG_PRINT(__FUNCDNAME__); }

};
