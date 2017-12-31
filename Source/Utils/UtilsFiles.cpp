#include "Utils/UtilsFiles.hpp"



std::unordered_map<std::string, std::string> ParseResourceFile(std::string filename)
{
  std::unordered_map<std::string, std::string> map;

  std::fstream fileObject("Resources/" + filename);
  if (!fileObject.is_open())
    AlertMessage("Could not open " + filename + " in the resouces folder!\nThis may cause unexpected behavior. Continue?");

  std::string buffer;
  while (std::getline(fileObject, buffer))
  {
    if (buffer.size() == 0)
      continue;

    int loc = 0;
    while (U_IsWhitespace(buffer[loc]))
      buffer = buffer.substr(1);

    if (buffer.size() == 0)
      continue;

    if (buffer[0] == '#')
      continue;

    size_t colonLoc = buffer.find_first_of(':');
    if (colonLoc == buffer.npos)
    {
      AlertMessage("There is an invalid field in" + filename + "!\nConfirm all lines are a single key:value. Want to skip this line and continue?");
      continue;
    }

    std::string left = buffer.substr(0, colonLoc);
    std::string right = buffer.substr(colonLoc + 1);
    map[U_Lowercase(left)] = U_Lowercase(right);
  }

  fileObject.close();
  return map;
}
