#pragma once
#include "ColliderComponent.h"
#include "cocos2d.h"

class BoxCollider : public ColliderComponent
{
public:
  BoxCollider();
  BoxCollider(cocos2d::Rect boxCollider);
  virtual ~BoxCollider();

  void          setRectangle(cocos2d::Rect boxRect);
  cocos2d::Rect getRectangle();

  virtual bool intersectsCollider(ColliderComponent* collider) override;
  virtual BoxCollider* clone() override;

private:
  cocos2d::Rect boxCollider_;
};

