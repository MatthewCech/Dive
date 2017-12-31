#pragma once
#include <unordered_map>
#include "Structures/Typedefs.hpp"
#include "Structures/TileVisual.hpp"
#include "Structures/Entity.hpp"




struct Tile
{
  // Constructors
  Tile () : RawRepresentation(' '), Visual(), TileContents(), Flags(0) {  } 
  Tile (char representation) : RawRepresentation(representation), Flags(0) {  }
  
  // Public member variables
  char RawRepresentation;                             // The raw ascii representation of the tile. Don't use for lookups.
  TileVisual Visual;                                  // The tile visual - could be ascii, could be a picture.
  std::unordered_map<ID_Entity, Entity> TileContents; // Keeps track of entities on a specific tile.
  size_t Flags;                                       // Keeps track of the type of tile this is.
};
