#include "Building.h"



Building::Building(cocos2d::Vec2 startPosition)
  : currentPosition_(startPosition)
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
}

std::shared_ptr<GameObject> Building::getTopElement()
{
  return elements_.back();
}

GameObject * Building::clone()
{
  return nullptr;
}
