#include "BoxCollider.h"


BoxCollider::BoxCollider(cocos2d::Rect boxRect, cocos2d::Node* parent)
  :boxRect_(boxRect), parent_(parent)
{
  boxCollider_ = cocos2d::DrawNode::create(); //autorelease object

  boxCollider_->retain();

  boxCollider_->setContentSize(boxRect.size);
  boxCollider_->drawSolidRect(boxRect.origin, boxRect.size, cocos2d::Color4F::RED);
  boxCollider_->setOpacity(60);
  parent->addChild(boxCollider_);

  boxCollider_->setVisible(Globals::DebugDrawColliders);
}


BoxCollider::~BoxCollider()
{
  boxCollider_->removeFromParent();
  boxCollider_->release();
}


void BoxCollider::setCollider(cocos2d::Rect boxRect, cocos2d::Node* parent)
{
  boxCollider_->removeFromParent();
  boxCollider_->release();
 
  boxRect_ = boxRect;
  parent_ = parent;

  boxCollider_ = cocos2d::DrawNode::create(); //autorelease object
  boxCollider_->retain();

  boxCollider_->setContentSize(boxRect.size);
  boxCollider_->drawSolidRect(boxRect.origin, boxRect.size, cocos2d::Color4F::RED);

  boxCollider_->setOpacity(60);
  parent->addChild(boxCollider_);

  boxCollider_->setVisible(Globals::DebugDrawColliders);  
}


bool BoxCollider::intersectsCollider(ColliderComponent* otherCollider)
{
  //bool isBoxCollider = ( typeid(otherCollider) == typeid(BoxCollider) );

  //if (isBoxCollider) {
  //  auto otherBoxCollider = static_cast<BoxCollider*>(otherCollider);
  //  return boxCollider_.intersectsRect(otherBoxCollider->getRectangle() );
  //}

  return false;
}

ColliderComponent* BoxCollider::clone(cocos2d::Node* parent)
{
  BoxCollider* component;
  component = new BoxCollider(boxRect_, parent);

  return component;
}
