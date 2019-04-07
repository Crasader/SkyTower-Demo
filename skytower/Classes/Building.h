#pragma once
#include "GameObject.h"
#include "Colleague.h"
#include <vector>
#include <memory>


class Building : public GameObject, public Colleague
{
public:
  Building(cocos2d::Vec2 startPosition, std::shared_ptr<Mediator> mediator);
  virtual ~Building();

  virtual void  update(float deltaTIme) override;
  virtual void  fixedUpdate(float deltaTime) override;

  void                        addElement( std::shared_ptr<GameObject> gameObject );
  std::shared_ptr<GameObject> getTopElement();

  virtual void  notify(NotifyState notify, int integer, Colleague* sender) override;
  
private:
  virtual GameObject* clone() override;

private:
  cocos2d::Vec2   currentPosition_;
  std::vector<std::shared_ptr<GameObject>> elements_;
};
