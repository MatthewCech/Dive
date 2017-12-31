#pragma once
#include <unordered_map>
#include "Structures/Typedefs.hpp"
#include "Structures/TileVisual.hpp"
#include "Structures/Entity.hpp"



struct Tile
{
  Tile () : RawRepresentation(' '), Visual(), TileContents() {  } 
  Tile (char representation) : RawRepresentation(representation) {  }
  
  char RawRepresentation;
  TileVisual Visual;
  std::unordered_map<ID_Entity, Entity> TileContents;
};