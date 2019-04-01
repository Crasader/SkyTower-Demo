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
  auto newPositon = cocos2d::Vec2(objectPosition.x, currentPosition_.y);
  gameObject->setPosition(newPositon);

  float objectHeight = gameObject->getCollider()->getSize().height;
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
