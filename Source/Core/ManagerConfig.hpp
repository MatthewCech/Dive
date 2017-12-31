#pragma once
#include "Core/ManagerBase.hpp"
#include <unordered_map>
#include "Graphics/console-utils.hpp"


class ManagerConfig : public ManagerBase
{
public:
  // Initialization and primary virtual functions
  void Init();
  void Update(UpdateInfo i) { }

  // Value manipulation
  void SetValue(const std::string &key, std::string value);
  std::string GetValueAsString(const std::string &key);
  double GetValueAsDouble(const std::string &key);
  bool GetValueAsBool(const std::string &key);
  RConsole::Color GetCharAsColor(char val) const;

private:
  // Private member funcs
  void requireKey(std::string str);

  // Private member variables
  std::unordered_map<std::string, std::string> _values;
};
