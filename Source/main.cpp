// Standard 
#include <iostream>

// My implementation
#include <ConsoleInput/console-input.h>
#include <RUtils/RMacros.hpp>
#include "Core/Engine.hpp"
#include "Core/ManagerInput.hpp"
#include "Core/ManagerEntity.hpp"
#include "Core/ManagerGraphics.hpp"


int main(int argc, char** argv)
{
  // Engine initialization
  Engine e;
  e.Add<ManagerInput>();
  e.Add<ManagerEntity>();
  e.Add<ManagerGraphics>();

  // Primary Loop
  while (e.Update()) { break; }

  // Hold at termination, as this is abnormal behavior.
  e.Shutdown();
  system("pause");
  return 0;
}
