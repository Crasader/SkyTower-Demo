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

void Building::update(float deltaTIme)
{
}

void Building::fixedUpdate(float deltaTime)
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
        this->send(NotifyState::AddScore, 100);

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

GameObject * Building::clone()
{
  return nullptr;
}
