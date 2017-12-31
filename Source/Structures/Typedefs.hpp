#pragma once
#include <string>


// ID typedefs
typedef size_t ID_Entity;
typedef std::string ID_Map;
typedef std::string ID_Room;

// Keys for general game config
#define KEY_GENERAL_START_MAP "startingmap"
#define KEY_GENERAL_PLAYER_ASCII "playersymbol"
#define KEY_GENERAL_WALLS_AS_219 "wallsassolidascii"

// Map keys
#define KEY_MAP_START "spawn"
#define KEY_MAP_WIDTH "width"
#define KEY_MAP_HEIGHT "height"

// flags in general
#define KEY_GENERAL_FLAG_WALL "wall"
#define KEY_GENERAL_FLAG_DOOR "door"
#define KEY_GENERAL_FLAG_GRASS "grass"
#define KEY_GENERAL_FLAG_WATER "water"
#define KEY_GENERAL_FLAG_FIRE  "fire"
