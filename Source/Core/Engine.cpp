#include "Engine.hpp"
#include "Structures/UpdateInfo.hpp"
#include <thread>


  ///////////////
 // Ctor/Dtor //
///////////////
Engine * Engine::Instance = nullptr;
Engine::Engine() 
  : _managers()
  , _managersOrdered()
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
  for (size_t i = 0; i < Instance->_managersOrdered.size(); ++i)
    Instance->_managersOrdered[i]->Update({ 0.016 });

  std::this_thread::sleep_for(std::chrono::milliseconds(1));

  return true;
}

void Engine::Shutdown()
{
  while (_managersOrdered.size() > 0)
  {
    ManagerBase *m = _managersOrdered.back();
    _managersOrdered.pop_back();
    m->Shutdown();
    delete m;
  }
}


  //////////////////////////////
 // Private member functions //
//////////////////////////////
void Engine::init()
{
  if (Instance == nullptr)
    Instance = this;
  else
    AlertMessage("Attempted to re-create the engine! Continue?");
}

void Engine::verifyInit()
{
  if (Instance == nullptr)
  {
    AlertMessage("Engine has not been initialized yet!\nWould you like to do so now?");
    Instance = new Engine();
  }
}