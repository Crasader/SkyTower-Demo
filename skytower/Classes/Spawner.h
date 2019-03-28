#pragma once

#include <string>
#include <map>
#include <memory>
#include "Globals.h"
#include "GameObject.h"

template<class T>
class Spawner
{
public:
           Spawner();
  virtual ~Spawner();

  void        addPrototype(T* object, const std::string& name);
  GameObject* spawn(const std::string& byName);

private:
  std::map<std::string, std::shared_ptr<T>> prototypes_;
};

