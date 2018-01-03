// Standard 
#include <iostream>
#include <random>
#include <time.h>
#include <string>

// My libs/etc
#include <ConsoleInput/console-input.h>
#include <RUtils/RMacros.hpp>

// My implementation
#include "Core/Engine.hpp"
#include "Core/ManagerInput.hpp"
#include "Core/ManagerLevel.hpp"
#include "Core/ManagerGraphics.hpp"
#include "Core/ManagerWorld.hpp"
#include "Core/ManagerConfig.hpp"



int main(int argc, char** argv)
{
  // Seed random
  if(argc == 2)
    std::srand(static_cast<unsigned int>(std::stoi(argv[1])));
  else
    std::srand(static_cast<unsigned int>(time(NULL)));

  // Engine initialization
  Engine e;
  Engine::Instance->Add<ManagerConfig>();
  Engine::Instance->Add<ManagerInput>();
  Engine::Instance->Add<ManagerWorld>();
  Engine::Instance->Add<ManagerLevel>();
  Engine::Instance->Add<ManagerGraphics>();

  // Primary Loop
  while (Engine::Instance->Update()); //{ break; }

  // Hold at termination, as this is abnormal behavior.
  Engine::Instance->Shutdown();
  system("pause");
  return 0;
}
