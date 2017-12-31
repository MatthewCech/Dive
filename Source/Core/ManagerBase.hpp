#pragma once
#include "Structures/UpdateInfo.hpp"
#include "RUtils/RMacros.hpp"


class ManagerBase
{
public:
  // Constructor/Destructor
  ManagerBase() { };
  ~ManagerBase() { };

  // Primary Functions
  virtual void Init() { };
  virtual void Update(UpdateInfo i) { };
  virtual void Shutdown() { DEBUG_PRINT("Shutting down: " << typeid(*this).name()); };
};
