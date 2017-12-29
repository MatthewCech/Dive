#pragma once
#include "Structures/Typedefs.hpp"


struct Entity
{
  // Constructor. No defaults!
  Entity(ID_Entity id) : ID(id) {  }
  Entity() = delete;

  // Operator overloading
  bool operator==(const Entity &rhs) { return ID == rhs.ID; }
  bool operator!=(const Entity &rhs) { return ID != rhs.ID; }
  operator ID_Entity() { return ID; }
  
  // Internal data
  const ID_Entity ID;
};
