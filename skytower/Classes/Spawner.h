#pragma once

#include <string>
#include <map>
#include <memory>
#include "Globals.h"

// Declaration //
template<typename T>
class Spawner
{
public:
           Spawner();
  virtual ~Spawner();

  void  addPrototype(T* object, const std::string& name);
  T*    spawn(const std::string& byName);

private:
  std::map<std::string, std::shared_ptr<T>> prototypes_;
};



// Definition //
template<typename T>
Spawner<T>::Spawner()
{
}

template<typename T>
Spawner<T>::~Spawner()
{
}


template<typename T>
void Spawner<T>::addPrototype(T * object, const std::string & name)
{
  prototypes_[name] = std::shared_ptr<T>(object);
}


template<typename T>
T* Spawner<T>::spawn(const std::string& byName)
{
  return prototypes_[byName]->clone();
}