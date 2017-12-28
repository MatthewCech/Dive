#pragma once
#include "Structures/UpdateInfo.hpp"



class ManagerBase
{
public:
  // Constructor/Destructor
  ManagerBase() { };
  ~ManagerBase() { };

  // Primary Functions
  virtual void Init() { };
  virtual void Update(UpdateInfo i) { };
  virtual void Shutdown() { };
};
