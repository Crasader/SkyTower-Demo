#pragma once
#include "cocos2d.h"

class ColliderComponent
{
public:
  ColliderComponent();
  virtual ~ColliderComponent();

  virtual cocos2d::Vec2 getOrigin() = 0;
  virtual cocos2d::Size getSize() = 0;
  virtual bool intersectsCollider(std::shared_ptr<ColliderComponent> collider) = 0;
  virtual ColliderComponent* clone(cocos2d::Node* parent) = 0;
};

