#include "Core/ManagerWorld.hpp"
#include <filesystem>

namespace fs = std::experimental::filesystem;

void ManagerWorld::Init()
{
  for (auto &dirEntry : fs::directory_iterator("Resources/"))
  {
    DEBUG_PRINT(dirEntry.path());
  }
}