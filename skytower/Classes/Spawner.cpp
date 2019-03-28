#include "Spawner.h"
#include "cocos2d.h"

template<class T>
Spawner<T>::Spawner()
{
}

template<class T>
Spawner<T>::~Spawner()
{
}



template<class T>
void Spawner<T>::addPrototype(T * object, const std::string & name)
{
  prototypes_[name] = std::shared_ptr<T>(object);
}

template<class T>
GameObject* Spawner<T>::spawn(const std::string& byName)
{
  return prototypes_[byName]->clone();
}

template<class T>
void Spawner<T>::empty()
{
}
