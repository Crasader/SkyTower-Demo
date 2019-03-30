
#include "GameScene.h"
#include "Globals.h"
#include "Enums.h"
#include "Spawner.h"
#include <memory>

USING_NS_CC;


Scene* GameScene::createScene()
{
  auto scene = Scene::create();
  auto layer = GameScene::create();


  scene->addChild(layer);
  return scene;
}

bool GameScene::init()
{
  if (!Layer::init()) {
    return false;
 }

  auto size = Director::getInstance()->getWinSize();


  //Spawn Background
  //title_ = std::unique_ptr<GameObject>(Globals::spawner.spawn("backsky"));
  //title_->getGraphic()->setParentNode(this, BACKGROUND);

  title_ = std::unique_ptr<GameObject>(Globals::spawner.spawn("backearth"));
  title_->getGraphic()->setParentNode(this, BACKGROUND);

  
  auto draw = DrawNode::create();
  draw->drawDot(Vec2(size / 2), 10.0f, Color4F::WHITE);
  this->addChild(draw);


  this->scheduleUpdate();
  return true;
}



