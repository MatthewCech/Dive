#pragma once
#include "ManagerBase.hpp"
#include <vector>


class Engine
{
public:
  // Ctor/Dtor
  Engine();
  ~Engine();

  // Public member functions
  template<typename T> void Add();
  bool Update();
  void Shutdown();

private:
  // Private member functions
  void init();
  void verifyInit();

  // Private variables
  static Engine *_instance;
  std::vector<ManagerBase *> _managers;
};


  //////////////////////////////
 // Template implementations //
//////////////////////////////
template<typename T> 
void Engine::Add() 
{ 
  verifyInit();
  T *m = new T(); 
  m->Init(); 
  _instance->_managers.push_back(m); 
}
