#pragma once
#include "ColliderComponent.h"
#include "Globals.h"
#include "cocos2d.h"

class BoxCollider : public ColliderComponent
{
private:
  BoxCollider();

public:
  BoxCollider(cocos2d::Rect boxRect, cocos2d::Node* parent);
  virtual ~BoxCollider();

  void setCollider(cocos2d::Rect boxRect, cocos2d::Node* parent);

  virtual bool intersectsCollider(ColliderComponent* collider) override;
  virtual ColliderComponent* clone(cocos2d::Node* parent) override;

private:
  cocos2d::DrawNode* boxCollider_;
  cocos2d::Rect      boxRect_;
  cocos2d::Node*     parent_;
};

