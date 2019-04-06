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

  virtual cocos2d::Vec2 getOrigin() override;
  virtual cocos2d::Size getSize() override;

  void               setBoxCollider(cocos2d::Rect boxRect, cocos2d::Node* parent);
  cocos2d::DrawNode* getBoxCollider();

  cocos2d::Rect      getBoxRect();

  virtual bool intersectsCollider(std::shared_ptr<ColliderComponent> collider) override;
  virtual ColliderComponent* clone(cocos2d::Node* parent) override;

private:
  cocos2d::DrawNode* boxCollider_;
  cocos2d::Rect      boxRect_; 
  cocos2d::Node*     parent_; 
};

