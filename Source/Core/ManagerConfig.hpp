#pragma once
#include "Core/ManagerBase.hpp"
#include <unordered_map>



class ManagerConfig : public ManagerBase
{
public:
  void Init();
  void Update(UpdateInfo i) { DEBUG_PRINT(__FUNCDNAME__); }

  void SetValue(const std::string &key, std::string value);
  std::string GetValueAsString(const std::string &key);
  double GetValueAsDouble(const std::string &key);

private:
  std::unordered_map<std::string, std::string> _values;
};
