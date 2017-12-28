#include "Core/ManagerWorld.hpp"
#include <filesystem>

namespace fs = std::experimental::filesystem;

#ifdef _WIN32
#include "windows.h"
fs::path GetBasePath(const std::string& path)
{
  const int maxPath = 260; // since it likes to forget what the MAX_PATH define is...
  HMODULE hModule = GetModuleHandleW(NULL);
  WCHAR c_path[maxPath];
  GetModuleFileNameW(hModule, c_path, maxPath);
  fs::path base_path = fs::path(c_path).parent_path();
  return canonical(base_path / path);
}
#else
fs::path GetBasePath(const std::string& path)
{
  return fs::path(path);
}
#endif

void ManagerWorld::Init()
{
  for (auto &dirEntry : fs::directory_iterator(GetBasePath(".")))
  {
    DEBUG_PRINT(dirEntry.path());
  }
}