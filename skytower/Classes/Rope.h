#pragma once
#include "GameObject.h"
#include "Colleague.h"
#include "cocos2d.h"

template<typename T> class Spawner;

class Rope : public GameObject, public Colleague
{
  enum RopeState {
    EMPTY,
    RELOADING,
    RELOADED,
    READY
  };

public:
  Rope( InputComponent* inputState, 
        cocos2d::Node* gameLayer, 
        std::list<std::shared_ptr<GameObject>>* objectsPool, 
        std::shared_ptr<Mediator> mediator );
  virtual ~Rope();

  GameObject*   clone();
  virtual void  update(float deltaTime) override;
  virtual void  fixedUpdate(float deltaTime) override;
  void          addElement(std::shared_ptr<GameObject> element);

private:
  void                        attachElement(std::shared_ptr<GameObject> element);
  std::shared_ptr<GameObject> detachElement();
  void                        attachNextElement();
  void                        setReadyState();

  virtual void  notify(NotifyState notify, int integer, Colleague* sender) override;

private:
  cocos2d::Node*        gameLayer_;
  std::list<std::shared_ptr<GameObject>>* pool_;

  cocos2d::Size         screenSize_;
  std::shared_ptr<GameObject> attachedElement_;
  RopeState             ropeState_{ EMPTY };

  cocos2d::Vec2         position_{ cocos2d::Vec2::ZERO };
  cocos2d::Vec2         vector_{ cocos2d::Vec2::ZERO };

  //Queue of waithing objects
  std::queue<std::shared_ptr<GameObject>> queue_;
};

