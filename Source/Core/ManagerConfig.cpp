#include <fstream>
#include <string>
#include "ManagerConfig.hpp"
#include "Core/Alert.hpp"
#include "Utils/UtilsString.hpp"
#include "Utils/UtilsFiles.hpp"


static std::unordered_map<std::string, RConsole::Color> colorLookup
{
  { "black", RConsole::BLACK },
  { "blue", RConsole::BLUE },
  { "green", RConsole::GREEN },
  { "cyan", RConsole::CYAN },
  { "red", RConsole::RED },
  { "magenta", RConsole::MAGENTA },
  { "brown", RConsole::BROWN },
  { "grey", RConsole::GREY },
  { "darkgrey", RConsole::DARKGREY },
  { "lightblue", RConsole::LIGHTBLUE },
  { "lightgreen", RConsole::LIGHTGREEN },
  { "lightcyan", RConsole::LIGHTCYAN },
  { "lightred", RConsole::LIGHTRED },
  { "lightmagenta", RConsole::LIGHTMAGENTA },
  { "yellow", RConsole::YELLOW },
  { "white", RConsole::WHITE }
};

// Gets character as color. If character is not found, we 
RConsole::Color ManagerConfig::GetCharAsColor(char val) const
{
  std::string str = " ";
  str[0] = val;
  auto iter = _values.find(str);
  if (iter != _values.end())
  {
    auto colorIter = colorLookup.find(iter->second);
    if (colorIter != colorLookup.end())
      return colorIter->second;
  }

  return RConsole::WHITE;
}

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
