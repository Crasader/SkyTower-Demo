#include "Building.h"
#include "Components\BoxCollider.h"

USING_NS_CC;

Building::Building(cocos2d::Vec2 startPosition, std::shared_ptr<Mediator> mediator)
  : currentPosition_(startPosition), Colleague(mediator)
{
}


Building::~Building()
{
}




void Building::addElement( std::shared_ptr<GameObject> gameObject )
{
  auto objectPosition = gameObject->getPosition();
  auto collisionRectOrigin = gameObject->getCollider()->getOrigin();
  auto collisionRectSize = gameObject->getCollider()->getSize();
  auto newPositon = cocos2d::Vec2(objectPosition.x, currentPosition_.y - collisionRectOrigin.y);
  gameObject->setPosition(newPositon);

  float objectHeight = collisionRectSize.height - collisionRectOrigin.y;
  currentPosition_.y += objectHeight;

  gameObject->setTag(ELEMENT_BUILDING);
  elements_.push_back(gameObject);

  send(NotifyState::ElementAdded);
}

std::shared_ptr<GameObject> Building::getTopElement()
{
  return elements_.back();
}

void Building::notify(NotifyState notify, int integer, Colleague* sender)
{
}

bool Building::intersectsCollider(std::shared_ptr<ColliderComponent> collider)
{
  //Get Collider of top element
  auto topObjectCollider = getTopElement()->getCollider();
  bool intersects = topObjectCollider->intersectsCollider(collider);
  return intersects;
}

void Building::checkIntersectObject(std::shared_ptr<GameObject> object)
{
  bool objectIsFreeElement = (object->getTag() == ELEMENT_FREE);
  if (objectIsFreeElement) {

    bool intesectBuildingAndElement = this->intersectsCollider(object->getCollider());
    if (intesectBuildingAndElement) {

      auto elementBoxCollider = std::static_pointer_cast<BoxCollider>(this->getTopElement()->getCollider());
      auto elementBoxColliderNode = elementBoxCollider->getBoxCollider();
      auto elementOrigin = elementBoxColliderNode->getParent()->convertToWorldSpace(elementBoxCollider->getOrigin());
      auto elementSize = elementBoxCollider->getSize();
      auto elementMiddle = Vec2(elementOrigin.x + elementSize.width / 2, elementOrigin.y);
      cocos2d::Rect elementRect = cocos2d::Rect(elementOrigin, elementSize);

      auto objectBoxCollider = std::static_pointer_cast<BoxCollider>(object->getCollider());
      auto objectBoxColliderNode = objectBoxCollider->getBoxCollider();
      auto objectOrigin = objectBoxColliderNode->getParent()->convertToWorldSpace(objectBoxCollider->getOrigin());
      auto objectSize = objectBoxCollider->getSize();
      auto objectMiddle = Vec2(objectOrigin.x + objectSize.width / 2, objectOrigin.y);
      cocos2d::Rect objectRect = cocos2d::Rect(objectOrigin, objectSize);

      auto objectStandingStill = elementRect.containsPoint(objectMiddle);


      if (objectStandingStill) {

        object->stopMovement();
        this->addElement(object);

        //Compute Scores        
        auto x1 = std::max(elementRect.origin.x, objectRect.origin.x);
        auto x2 = std::min(elementRect.origin.x + elementRect.size.width, objectRect.origin.x + objectRect.size.width);
        auto percent = (100 * (x2 - x1)) / objectRect.size.width;

        int score;
        if (percent >= 99) {
          score = 500;
        }
        if (percent >= 90 && percent < 99) {
          score = 250;
        };
        if (percent >= 70 && percent < 90) {
          score = 100;
        };
        if (percent < 70) {
          score = 50;
        };

        this->send(NotifyState::AddScore, score);

        //// Add squash action
        auto scale = ScaleBy::create(0.1f, 1.2f, 0.8f);
        auto down = EaseOut::create(scale, 2.0f);
        auto up = EaseIn::create(scale->reverse(), 1.5f);
        auto action = Sequence::create(down, up, nullptr);
        object->getCocosNode()->runAction(action);
        ////
      }
      else {
        //object is Falling
        object->setTag(ELEMENT_FALLING);
        object->setVelocity(Vec2::ZERO);
        float angle = -360.0f;

        bool objectFallRight = objectMiddle.x > elementMiddle.x;
        if (objectFallRight) {
          angle *= -1;
        }

        auto rotate = RotateBy::create(4.0f, angle);
        auto action = RepeatForever::create(rotate);
        object->getCocosNode()->runAction(action);
      }
    }
  }


}

float Building::computeBalance()
{
  auto i = elements_.begin();
  i++;

  //Get first (Base) element (after grass)
  auto elementBoxCollider = std::static_pointer_cast<BoxCollider>( (*i)->getCollider() );
  auto elementBoxColliderNode = elementBoxCollider->getBoxCollider();
  auto elementOrigin = elementBoxColliderNode->getParent()->convertToWorldSpace(elementBoxCollider->getOrigin());
  auto elementSize = elementBoxCollider->getSize();
  auto elementMiddle = elementOrigin.x + elementSize.width / 2;

  auto baseMinX = elementOrigin.x;
  auto baseMaxX = elementOrigin.x + elementSize.width;

  auto buildingMinX = baseMinX;
  auto buildingMaxX = baseMaxX;

  float tempMinX, tempMaxX;

  //Compute mixX and maxX
  i++;
  for (; i != elements_.end(); i++) {
    //Get next element
    elementBoxCollider = std::static_pointer_cast<BoxCollider>((*i)->getCollider());
    elementBoxColliderNode = elementBoxCollider->getBoxCollider();
    elementOrigin = elementBoxColliderNode->getParent()->convertToWorldSpace(elementBoxCollider->getOrigin());
    elementSize = elementBoxCollider->getSize();

    tempMinX = elementOrigin.x;
    tempMaxX = elementOrigin.x + elementSize.width;

    if (tempMinX < buildingMinX) {
      buildingMinX = tempMinX;
    }

    if (tempMaxX > buildingMaxX)
    {
      buildingMaxX = tempMaxX;
    }
  };


  auto buildingMiddle = buildingMinX + (buildingMaxX - buildingMinX) / 2;

  auto distanceFromMidPoints = buildingMiddle - elementMiddle;
  auto balance = (distanceFromMidPoints / 50) * elements_.size();
  return balance;
}

void Building::setStagger(float balance)
{
  staggerValue_ = balance; 

  auto size = elements_.size();

  if (size > 2) {
    float index = 0;
    float interval = balance / size;

    
    MoveBy* move = MoveBy::create(staggerDuration_, Vec2(index, 0));
    MoveBy* moveRev = MoveBy::create(staggerDuration_, Vec2(-index, 0));
    EaseInOut* ease = EaseInOut::create(move, 2.0f);
    EaseInOut* easeRev = EaseInOut::create(moveRev, 2.0f);
    RepeatForever* action = RepeatForever::create(Sequence::create(ease, easeRev, nullptr));

    for (auto i = elements_.begin(); i != elements_.end(); i++) {
      move = MoveBy::create(staggerDuration_, Vec2(index, 0));
      moveRev = MoveBy::create(staggerDuration_, Vec2(-index, 0));
      ease = EaseInOut::create(move, 2.0f);
      easeRev = EaseInOut::create(moveRev, 2.0f);
      action = RepeatForever::create(Sequence::create(ease, easeRev, nullptr));
      (*i)->getCocosNode()->stopAllActions();
      (*i)->getCocosNode()->runAction(action);
      index += interval;
    }

  }

}

GameObject * Building::clone()
{
  return nullptr;
}
