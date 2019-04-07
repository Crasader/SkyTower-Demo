#pragma once

#include <string>
#include <memory>
#include "cocos2d.h"
#include "Components\PhysicComponent.h"
#include "Components\GraphicComponent.h"
#include "Components\InputComponent.h"
#include "Components\PlayerInputComponent.h"
#include "Components\ColliderComponent.h"
#include "Enums.h"


class GameObject
{
public:
  GameObject( GraphicComponent*  graphic = nullptr, 
              PhysicComponent*   physic = nullptr,
              ColliderComponent* collider = nullptr,
              InputComponent*    input = nullptr);

  virtual ~GameObject();

  virtual GameObject*  clone();
  virtual void        update(float deltaTime);
  virtual void   fixedUpdate(float deltaTime);
  
  //bool intersectsObject(std::shared_ptr<GameObject> gameObject);

  std::shared_ptr  <InputComponent>  getInput();
  std::shared_ptr <PhysicComponent>  getPhysic();
  std::shared_ptr<GraphicComponent>  getGraphic();
  std::shared_ptr<ColliderComponent> getCollider();

  void setInput(InputComponent* input);
  void setPhysic(PhysicComponent* physic);
  void setGraphic(GraphicComponent* graphic);
  void setCollider(ColliderComponent* collider);

  std::shared_ptr<GameObject>       getChild();
  void setChild(GameObject* gameObject);

  void stopMovement();

  void setTag(int tag);
  int  getTag();

  bool  isReadyToDie{ false };


  ////WRAPPERS
  //Graphics wrappers
  cocos2d::Node*    getCocosNode() { return getGraphic()->getNode(); };
  void              setPosition(cocos2d::Vec2 position) { getGraphic()->setPosition(position); };
  cocos2d::Vec2     getPosition() { return getGraphic()->getPosition(); };
  void              setRotation(float angle) { getGraphic()->setRotation(angle); };
  float             getRotation() { return getGraphic()->getRotation(); };
  void              setColor(cocos2d::Color3B color) { getGraphic()->setColor(color); };
  cocos2d::Color3B  getColor() { return getGraphic()->getColor(); };
  //Physic wrappers
  void          setVelocity(cocos2d::Vec2 velocity) { getPhysic()->setVelocity(velocity); };
  cocos2d::Vec2 getVelocity() { return getPhysic()->getVelocity(); };
  void          setGravity(cocos2d::Vec2 gravity) { getPhysic()->setGravity(gravity); };
  cocos2d::Vec2 getGravity() { return getPhysic()->getGravity(); };
  void          setSpeed(float speed) { getPhysic()->setSpeed(speed); };
  float         getSpeed() { return getPhysic()->getSpeed(); };
  //Collider wrappwers
  virtual bool  intersectsCollider(std::shared_ptr<ColliderComponent> collider) { return getCollider()->intersectsCollider(collider); };
  ////WRAPPERS


protected:
  std::shared_ptr  <InputComponent>  input_;
  std::shared_ptr <PhysicComponent>  physic_;
  std::shared_ptr<GraphicComponent>  graphic_;
  std::shared_ptr<ColliderComponent> collider_;

  std::shared_ptr<GameObject>       child_;

  int tag_{ NONE };

};

