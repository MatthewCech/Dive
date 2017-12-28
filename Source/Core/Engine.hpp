#pragma once
#include "ManagerBase.hpp"
#include <vector>
#include <typeinfo>
#include <typeindex>
#include "Alert.hpp"
#include <unordered_map>


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
  std::vector<ManagerBase *> _managersOrdered;
  std::unordered_map<std::type_index, ManagerBase *> _managers;
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
  
  auto iter = Instance->_managers.find(typeid(T));
  if(iter != Instance->_managers.end())
    AlertMessage(L"You are trying to add two of the same type of manager!\nThis may cause unexpected Behavior. Continue?");

  Instance->_managers[typeid(T)] = m;
  Instance->_managersOrdered.push_back(m);
}

// Acceptable, w/ <10 items to iterate over.
// Will be faster than unordered_map.
template<typename T> 
T *Engine::Get()
{
  verifyInit();
  return static_cast<T*>(Instance->_managersOrdered.find(typeid(T)));
}
