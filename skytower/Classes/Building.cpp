#include "Building.h"



Building::Building(cocos2d::Vec2 startPosition)
  : startPosition_(startPosition), currentPosition_(startPosition)
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
  float objectHeight = gameObject->getGraphic()->getNode()->getBoundingBox().size.height;
  currentPosition_ += cocos2d::Vec2(0, objectHeight);
  elements_.push_back(gameObject);
}

GameObject * Building::clone()
{
  return nullptr;
}
