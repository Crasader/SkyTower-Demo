#include "BoxCollider.h"


BoxCollider::BoxCollider(cocos2d::Rect boxRect, cocos2d::Node* parent)
  :boxRect_(boxRect), parent_(parent)
{

  boxCollider_ = cocos2d::DrawNode::create(); //autorelease object
  boxCollider_->retain();

  boxCollider_->setContentSize(boxRect_.size);
  cocos2d::Vec2 boxRectDest;
  boxRectDest.x = boxRect_.origin.x + boxRect_.size.width;
  boxRectDest.y = boxRect_.origin.y + boxRect_.size.height;
  boxCollider_->drawSolidRect(boxRect_.origin, boxRectDest, cocos2d::Color4F::RED);

  boxCollider_->setOpacity(60);
  parent_->addChild(boxCollider_);

  boxCollider_->setVisible(Globals::DebugDrawColliders);
}


BoxCollider::~BoxCollider()
{
  boxCollider_->removeFromParent();
  boxCollider_->release();
}

cocos2d::Vec2 BoxCollider::getOrigin()
{
  return boxRect_.origin;
}

cocos2d::Size BoxCollider::getSize()
{
  return boxRect_.size;
}


void BoxCollider::setBoxCollider(cocos2d::Rect boxRect, cocos2d::Node* parent)
{
  boxCollider_->removeFromParent();
  boxCollider_->release();
 
  boxRect_ = boxRect;
  parent_ = parent;

  boxCollider_ = cocos2d::DrawNode::create(); //autorelease object
  boxCollider_->retain();

  boxCollider_->setContentSize(boxRect_.size);
  cocos2d::Vec2 boxRectDest;
  boxRectDest.x = boxRect_.origin.x + boxRect_.size.width;
  boxRectDest.y = boxRect_.origin.y + boxRect_.size.height;
  boxCollider_->drawSolidRect(boxRect_.origin, boxRectDest, cocos2d::Color4F::RED);

  boxCollider_->setOpacity(60);
  parent_->addChild(boxCollider_);

  boxCollider_->setVisible(Globals::DebugDrawColliders);  
}

cocos2d::DrawNode * BoxCollider::getBoxCollider()
{
  return boxCollider_;
}

cocos2d::Rect BoxCollider::getBoxRect()
{
  return boxRect_;
}


bool BoxCollider::intersectsCollider(std::shared_ptr<ColliderComponent> otherCollider)
{
  //try cast ColliderComponent to BoxCollider
  //if true, check Rectangle intersection
  auto otherBoxCollider = std::static_pointer_cast<BoxCollider>(otherCollider);

  if (otherBoxCollider) {

    auto objectOrigin = getBoxCollider()->getParent()->convertToWorldSpace(this->getOrigin());
    auto objectSize = this->getSize();
    cocos2d::Rect objectRect = cocos2d::Rect(objectOrigin, objectSize);

    auto otherBoxColliderNode = otherBoxCollider->getBoxCollider();
    auto otherObjectOrigin = otherBoxColliderNode->getParent()->convertToWorldSpace(otherBoxCollider->getOrigin());
    auto otherObjectSize = otherBoxCollider->getSize();
    cocos2d::Rect otherObjectRect = cocos2d::Rect(otherObjectOrigin, otherObjectSize);

    bool intersects = objectRect.intersectsRect(otherObjectRect);
    
    //debug draw collisions
    /*if (intersects) {
      auto drawnode = cocos2d::DrawNode::create(); //autorelease object

      drawnode->drawSolidRect(objectRect.origin, objectRect.origin + objectRect.size, cocos2d::Color4F::RED);
      drawnode->drawSolidRect(otherObjectRect.origin, otherObjectRect.origin + otherObjectRect.size, cocos2d::Color4F::BLUE);
      parent_->getParent()->addChild(drawnode, FOREGROUND);
    }*/

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
