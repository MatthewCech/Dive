#pragma once
#include "Core/ManagerBase.hpp"
#include <unordered_map>
#include "Graphics/console-utils.hpp"


class ManagerConfig : public ManagerBase
{
public:
  void Init();
  void Update(UpdateInfo i) { }

  void SetValue(const std::string &key, std::string value);
  std::string GetValueAsString(const std::string &key);
  double GetValueAsDouble(const std::string &key);
  RConsole::Color GetCharAsColor(char val) const;

private:
  std::unordered_map<std::string, std::string> _values;
};
