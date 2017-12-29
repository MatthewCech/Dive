#include "Core/ManagerWorld.hpp"
#include "Utils/UtilsString.hpp"
#include "Core/Alert.hpp"
#include <filesystem>
#include <string>
#include <fstream>



// filesystem namespace for this file. Used because it is currently experiemntal.
namespace fs = std::experimental::filesystem;

// Reads in all .room and .map files.
void ManagerWorld::Init()
{
  for (auto &dirEntry : fs::directory_iterator("Resources/"))
  {
    // Confirm the file has an extension. This is what we'll be going for regardless of OS.
    if (dirEntry.path().has_extension())
    {
      std::string extension = dirEntry.path().extension().string();
      U_Lowercase(extension);
      
      // Parse out rooms! Rooms are stored by name and data.
      if (extension == "room")
      {
        // Parse name and make it case insensitive.
        ID_Room name;
        if (dirEntry.path().has_filename())
          name = dirEntry.path().filename().string();
        else
          AlertMessage(L"You have a .room file that has no name.\nThis may cause issues if referenced. Proceed?");
        U_Lowercase(name);

        // Open the file.
        std::fstream fileObject(dirEntry.path());
        if (!fileObject.is_open())
          AlertMessage(L"One of the .room files failed to open.\nConfirm that nothing is open and try again!");

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
          AlertMessage(L"A .room file has either a width or height of 0! This will cause issues if referenced. Continue?");
          _rooms.insert(std::make_pair(name, Room(0, 0, name)));
          continue;
        }
        else if (lines.size() <= 2 || longest <= 2)
          AlertMessage(L"A .room file seems impractically small, with either a width of height of <= 2. This may cause issues if referenced. Continue?");
        else if (_rooms.find(name) != _rooms.end())
          AlertMessage(L"You have two .room files with the same name!\nNote that capital letters do not differentiate names.\nIf you continue, the already read file will be overwritten. Continue?");

        // Create the room and store it under the name. At this point, name is unique
        Room room(longest, lines.size(), name);
        for (size_t y = 0; y < lines.size(); ++y)
          for (size_t x = 0; x < lines[y].length(); ++x)
            room.Tiles[x][y] = lines[y][x];
        
        _rooms[name] = room;
      }
      else if (extension == "map")
      {
        AlertMessage(L"Files with the .map extension are currently not supported.\nDo you want to proceed?");

      }
    }
    DEBUG_PRINT(dirEntry.path());
  }
}