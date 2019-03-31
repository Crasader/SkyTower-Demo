#pragma once
#include "GameObject.h"
#include <vector>
#include <memory>


class Building : public GameObject
{
public:
  Building(cocos2d::Vec2 startPosition);
  virtual ~Building();

  virtual void update(float deltaTIme) override;
  virtual void fixedUpdate(float deltaTime) override;

  void addElement( std::shared_ptr<GameObject> gameObject );
  
private:
  virtual GameObject* clone() override;

private:
  cocos2d::Vec2   startPosition_;
  cocos2d::Vec2   currentPosition_;
  std::vector<std::shared_ptr<GameObject>> elements_;
};
