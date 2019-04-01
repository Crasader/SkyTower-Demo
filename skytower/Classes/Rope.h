#pragma once
#include "GameObject.h"
//#include "cocos2d.h"

//template<typename T> class Spawner;

class Rope : public GameObject
{
public:
  Rope();
  virtual ~Rope();

  virtual void  init();

  GameObject* clone();
  virtual void        update(float deltaTime);
  virtual void   fixedUpdate(float deltaTime);
    
private:
  //Node* layer_;
  //Node* gameLayer_;
  //Spawner<GameObject>* spawner_;

  //Size screenSize_;
};

