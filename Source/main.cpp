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
  Engine::Instance->Add<ManagerInput>();
  Engine::Instance->Add<ManagerEntity>();
  Engine::Instance->Add<ManagerGraphics>();
  Engine::Instance->Get<ManagerGraphics>();
  // Primary Loop
  while (Engine::Instance->Update()) { break; }

  // Hold at termination, as this is abnormal behavior.
  Engine::Instance->Shutdown();
  system("pause");
  return 0;
}
