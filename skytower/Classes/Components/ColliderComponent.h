#pragma once
#include "cocos2d.h"

class ColliderComponent
{
public:
  ColliderComponent();
  virtual ~ColliderComponent();

  virtual bool intersectsCollider(std::shared_ptr<ColliderComponent> collider) = 0;
  virtual ColliderComponent* clone(cocos2d::Node* parent) = 0;
};

