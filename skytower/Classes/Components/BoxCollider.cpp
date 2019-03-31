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


void BoxCollider::setBoxCollider(cocos2d::Rect boxRect, cocos2d::Node* parent)
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

cocos2d::DrawNode * BoxCollider::getBoxCollider()
{
  return boxCollider_;
}


bool BoxCollider::intersectsCollider(std::shared_ptr<ColliderComponent> otherCollider)
{
  bool isBoxCollider = ( typeid(otherCollider) == typeid(BoxCollider) );

  if (isBoxCollider) {
    auto otherBoxCollider = std::static_pointer_cast<BoxCollider>(otherCollider)->getBoxCollider();

    auto objectOrigin = boxCollider_->getParent()->convertToWorldSpace(boxCollider_->getBoundingBox().origin);
    auto objectSize = boxCollider_->getBoundingBox().size;
    cocos2d::Rect objectRect = cocos2d::Rect(objectOrigin, objectSize);

    auto otherObjectOrigin = otherBoxCollider->getParent()->convertToWorldSpace(otherBoxCollider->getBoundingBox().origin);
    auto otherObjectSize = otherBoxCollider->getBoundingBox().size;
    cocos2d::Rect otherObjectRect = cocos2d::Rect(otherObjectOrigin, otherObjectSize);

    bool intersects = objectRect.intersectsRect(otherObjectRect);
    return intersects;
  }

  return false;
}

ColliderComponent* BoxCollider::clone(cocos2d::Node* parent)
{
  BoxCollider* component;
  component = new BoxCollider(boxRect_, parent);

  return component;
}
