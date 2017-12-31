#include <fstream>
#include <string>
#include "ManagerConfig.hpp"
#include "Core/Alert.hpp"
#include "Utils/UtilsString.hpp"
#include "Utils/UtilsFiles.hpp"


void ManagerConfig::Init()
{
  _values = ParseResourceFile("general.conf");
}


  ////////////////////////
 // Value manupulation //
////////////////////////
void ManagerConfig::SetValue(const std::string &key, std::string value)
{
  _values[key] = value;
}

std::string ManagerConfig::GetValueAsString(const std::string &key)
{
  if (_values.find(key) == _values.end())
    return "";
  return _values[key];
}

double ManagerConfig::GetValueAsDouble(const std::string &key)
{
  if (_values.find(key) == _values.end())
    return 0;
  return std::stod(_values[key]);
}
