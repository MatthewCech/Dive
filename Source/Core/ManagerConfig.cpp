#include <fstream>
#include <string>
#include "ManagerConfig.hpp"
#include "Core/Alert.hpp"
#include "Utils/UtilsString.hpp"
#include "Utils/UtilsFiles.hpp"
#include "Structures/Typedefs.hpp"


void ManagerConfig::Init()
{
  _values = ParseResourceFile("general.conf");
  requireKey(KEY_GENERAL_START_MAP);
  requireKey(KEY_GENERAL_PLAYER_ASCII);
  requireKey(KEY_GENERAL_WALLS_AS_219);
}

  ////////////////////////
 // Value manupulation //
////////////////////////
// Convert values to a type and hand them back, or set values with a new string.
// All of these will fail safely if the value can not be found.
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
bool ManagerConfig::GetValueAsBool(const std::string &key)
{
  if (_values.find(key) == _values.end())
    return false;
  return U_Lowercase(_values[key]) == "true";

}
static std::unordered_map<std::string, RConsole::Color> _colorLookup
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

// Gets character as color. If character is not found, we return a default.
RConsole::Color ManagerConfig::GetCharAsColor(char val) const
{
  std::string str = " ";
  str[0] = val;
  auto iter = _values.find(str);
  if (iter != _values.end())
  {
    auto colorIter = _colorLookup.find(iter->second);
    if (colorIter != _colorLookup.end())
      return colorIter->second;
  }

  return RConsole::WHITE;
}


  //////////////////////////
 // Private member funcs //
//////////////////////////
// Require that _values has a certain key it it.
void ManagerConfig::requireKey(std::string key)
{
  auto iter = _values.find(key);
  if (iter == _values.end())
    AlertMessage("The required key " + key + " is not properly formatted  or\ndoes not exist in in general.conf!\nContinue anyways?");
}
