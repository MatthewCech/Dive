#pragma once
#include "ManagerBase.hpp"
#include <vector>
#include <typeinfo>


class Engine
{
public:
  // Ctor/Dtor
  Engine();
  ~Engine();

  // Public member functions
  template<typename T> void Add();
  template<typename T> T *Get();
  bool Update();
  void Shutdown();

  // Public member variables
  static Engine * Instance;
private:
  // Private member functions
  void init();
  void verifyInit();

  // Private variables
  std::vector<ManagerBase *> _managers;
};


  //////////////////////////////
 // Template implementations //
//////////////////////////////
// Add item, make before additon to initialize.
template<typename T> 
void Engine::Add() 
{ 
  verifyInit();
  T *m = new T(); 
  m->Init(); 
  Instance->_managers.push_back(m); 
}

// Acceptable, w/ <10 items to iterate over.
// Will be faster than unordered_map.
template<typename T> 
T *Engine::Get()
{
  verifyInit();
  for (int i = 0; i < Instance->_managers.size(); ++i)
    if (typeid(T) == typeid(*(Instance->_managers[i])))
      return Instance->_managers[i];
}
