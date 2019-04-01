#pragma once

#include <memory>
#include "cocos2d.h"
#include "GameObject.h"


class Rope;
class Building;

class GameScene : public cocos2d::Layer
{
public:
  static cocos2d::Scene* createScene();
  virtual bool init();
  CREATE_FUNC(GameScene);

  virtual void update(float deltaTime) override;
  void fixedUpdate(float deltaTime);

  void updateView();

  void onMouseDown(cocos2d::Event* event);

private:
  cocos2d::Size    screenSize_;

  cocos2d::Node*   gameLayer_;
  cocos2d::Vec2    gameLayerPos_;
  std::unique_ptr<GameObject>  backgroundSky_;
  std::unique_ptr<GameObject>  backgroundEarth_;

  std::shared_ptr<Rope>rope_;
  std::shared_ptr<Building>building_;
  std::list<std::shared_ptr<GameObject>> objectsPool_;

  //fixed update variables
  float fixedTimeCounter{ 0.0f };

};
