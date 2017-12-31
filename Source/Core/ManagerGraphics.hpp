#pragma once
#include "Core/ManagerBase.hpp"
#include "RUtils/RMacros.hpp"




class ManagerGraphics : public ManagerBase
{
public:
  void Init();
  void Update(UpdateInfo i);

private:
  size_t _width;
  size_t _height;
};
