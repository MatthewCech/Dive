#include "Engine.hpp"
#include "Alert.hpp"
#include "Structures/UpdateInfo.hpp"



  ///////////////
 // Ctor/Dtor //
///////////////
Engine * Engine::_instance = nullptr;
Engine::Engine() : _managers()
{
  init();
}

Engine::~Engine()
{
  Shutdown();
}

  /////////////////////////////
 // Public member functions //
/////////////////////////////
// Primary engine update. Passes updateInfo object to managers.
bool Engine::Update()
{
  for (size_t i = 0; i < _instance->_managers.size(); ++i)
    _instance->_managers[i]->Update({ 0.016 });

  return true;
}

void Engine::Shutdown()
{
  while (_managers.size() > 0)
  {
    ManagerBase *m = _managers.back();
    _managers.pop_back();
    m->Shutdown();
    delete m;
  }
}


  //////////////////////////////
 // Private member functions //
//////////////////////////////
void Engine::init()
{
  if (_instance == nullptr)
    _instance = this;
  else
    AlertMessage("Attempted to re-create the engine!");
}

void Engine::verifyInit()
{
  if (_instance == nullptr)
  {
    AlertMessage("Engine has not been initialized yet!\nWould you like to do so now?");
    _instance = new Engine();
  }
}