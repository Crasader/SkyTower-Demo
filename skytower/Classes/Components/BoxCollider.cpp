#include "BoxCollider.h"


BoxCollider::BoxCollider(cocos2d::Rect boxCollider, cocos2d::Node parent)
  :boxCollider_(boxCollider)
{

  auto draw = DrawNode::create();

  draw->drawSolidRect(Vec2(0, 0), Vec2(gameObject->getCocosNode()->getContentSize().width, 50.0f), Color4F::RED);
  draw->setOpacity(40);
  gameLayer_->addChild(draw);
  gameObject->getCocosNode()->addChild(draw);

}


BoxCollider::BoxCollider(cocos2d::Rect boxCollider, cocos2d::Node parent)
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::setRectangle(cocos2d::Rect boxRect)
{
  boxCollider_ = boxRect;
}

cocos2d::Rect BoxCollider::getRectangle()
{
  return boxCollider_;
}

bool BoxCollider::intersectsCollider(ColliderComponent* otherCollider)
{
  bool isBoxCollider = ( typeid(otherCollider) == typeid(BoxCollider) );

  if (isBoxCollider) {
    auto otherBoxCollider = static_cast<BoxCollider*>(otherCollider);
    return boxCollider_.intersectsRect(otherBoxCollider->getRectangle() );
  }

  return false;
}

BoxCollider* BoxCollider::clone()
{
  return new BoxCollider(boxCollider_);
}
