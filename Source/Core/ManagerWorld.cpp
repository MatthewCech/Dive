#include <filesystem>
#include <string>
#include <fstream>
#include "Core/ManagerWorld.hpp"
#include "Utils/UtilsString.hpp"
#include "Core/Alert.hpp"
#include "Utils/UtilsFiles.hpp"
#include "Core/Engine.hpp"
#include "Core/ManagerConfig.hpp"

// filesystem namespace for this file. Used because it is currently experiemntal.
namespace fs = std::experimental::filesystem;

static void verifyKey(const std::string &key, const std::string &filename, const std::unordered_map<std::string, std::string> &map)
{
  if (map.find("spawn") == map.end())
    AlertMessage(filename + " does not have a key of type " + key + "!\n Not having this may be a serious issue. Continue?");
}

// Reads in all .room and .map files.
void ManagerWorld::Init()
{
  loadRooms();
  loadMaps();
}

void ManagerWorld::loadRooms()
{
  const ManagerConfig* mconf = Engine::Instance->Get<ManagerConfig>();

  for (auto &dirEntry : fs::directory_iterator("Resources/"))
  {
    // Confirm the file has an extension. This is what we'll be going for regardless of OS.
    if (dirEntry.path().has_extension())
    {
      std::string extension = dirEntry.path().extension().string();
      U_Lowercase(extension);

      // Parse out rooms! Rooms are stored by name and data.
      if (extension == ".room")
      {
        // Parse name and make it case insensitive.
        ID_Room name;
        if (dirEntry.path().has_filename())
          name = dirEntry.path().filename().string();
        else
          AlertMessage("You have a .room file that has no name.\nThis may cause issues if referenced. Proceed?");
        U_Lowercase(name);

        // Open the file.
        std::fstream fileObject(dirEntry.path());
        if (!fileObject.is_open())
          AlertMessage("The " + name + " .room file failed to open.\nConfirm that it is not open. Would you like to continue regardless?");

        // Parse. Size of vector will be map height. Each string will be up to max width.
        std::vector<std::string> lines;
        std::string buffer;
        size_t longest = 0;
        while (std::getline(fileObject, buffer))
        {
          if (buffer.length() > longest)
            longest = buffer.length();

          lines.push_back(buffer);
        }

        // A few sanity checks to ensure the room seems playable before proceeding, and has a unique name.
        if (lines.size() == 0 || longest == 0)
        {
          AlertMessage("A .room file has either a width or height of 0! This will cause issues if referenced. Continue?");
          _rooms.insert(std::make_pair(name, Room(0, 0, name)));
          continue;
        }
        else if (lines.size() <= 2 || longest <= 2)
          AlertMessage(name + ".room file seems impractically small, with either a width of height of <= 2. This may cause issues if referenced. Continue?");
        else if (_rooms.find(name) != _rooms.end())
          AlertMessage("You have two .room files with the same name: " + name + "!\nNote that capital letters do not differentiate names.\nIf you continue, the already read file will be overwritten. Continue?");

        // Create the room and store it under the name. At this point, name is unique
        Room room(longest, lines.size(), name);
        for (size_t y = 0; y < lines.size(); ++y)
          for (size_t x = 0; x < lines[y].length(); ++x)
          {
            room.Tiles[x][y].RawRepresentation = lines[y][x];
            room.Tiles[x][y].Visual.ASCII = lines[y][x];
            char c = room.Tiles[x][y].Visual.ASCII;
            room.Tiles[x][y].Visual.ASCIIColor = mconf->GetCharAsColor(c);
          }

        _rooms[name] = room;
      }
    }
  }
}

void ManagerWorld::loadMaps()
{
  for (auto &dirEntry : fs::directory_iterator("Resources/"))
  {
    // Confirm the file has an extension. This is what we'll be going for regardless of OS.
    if (dirEntry.path().has_extension())
    {
      std::string extension = dirEntry.path().extension().string();
      U_Lowercase(extension);

      if (extension == ".map")
      {
        ID_Room name;
        if (dirEntry.path().has_filename())
          name = dirEntry.path().filename().string();
        else
          AlertMessage("You have a .map file that has no name.\nThis may cause issues if referenced. Proceed?");

        // Parse the map then make it lowercase.
        std::unordered_map<std::string, std::string> parsed = ParseResourceFile(name);
        U_Lowercase(name);

        verifyKey(MAP_WIDTH, name, parsed);
        verifyKey(MAP_HEIGHT, name, parsed);
        verifyKey(MAP_START, name, parsed); // perhaps not required...

        auto iter = _rooms.find(parsed[MAP_START]);
        if (iter == _rooms.end())
          AlertMessage("The specified room, " + parsed[MAP_START] + ", could not be found!\n Please verify that .room file is in the resources folder!\nTry to continue?");

        // get specific values then initialize.
        double width = std::stod(parsed["width"]);
        double height = std::stod(parsed["height"]);
        Map map(static_cast<int>(width), static_cast<int>(height), name, iter->second);
        _maps[name] =  map;
      }
    }
  }
}

Map &ManagerWorld::GetMap(ID_Map m)
{
  return _maps[m];
}

