
#include "GameScene.h"
#include "Globals.h"
#include "Enums.h"
#include "Spawner.h"
#include <memory>
#include <string>

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

  GameObject* gameObject;

  auto screenSize_ = Director::getInstance()->getWinSize();

  gameLayer_ = Node::create();
  this->addChild(gameLayer_);

  auto initialPosition(Vec2(screenSize_.width / 2, 200));
  building_ = std::make_unique<Building>(initialPosition);

  gameObject = Globals::spawner.spawn("element-grass");
  gameLayer_->addChild( gameObject->getCocosNode() );
  building_->addElement( std::shared_ptr<GameObject>(gameObject) );


  //Spawn Background
  backgroundSky_ = std::unique_ptr<GameObject>(Globals::spawner.spawn("backsky"));
  backgroundSky_->getGraphic()->setParentNode(this, BACKGROUND);

  backgroundEarth_ = std::unique_ptr<GameObject>(Globals::spawner.spawn("backearth"));
  backgroundEarth_->getGraphic()->setParentNode(gameLayer_, BACKGROUND);



  gameObject = Globals::spawner.spawn("element-balcon-Blue");
  gameObject->setPosition( Vec2(screenSize_.width / 2, screenSize_.height) );
  gameObject->setRotation(40.0f);
  gameLayer_->addChild( gameObject->getGraphic()->getNode() );
  objectsPool_.push_back(std::shared_ptr<GameObject>(gameObject));

  
  auto draw = DrawNode::create();

  draw->drawSolidRect(Vec2(0, 0), Vec2(gameObject->getCocosNode()->getContentSize().width, 50.0f), Color4F::RED);
  draw->setOpacity(40);
  gameLayer_->addChild(draw);
  gameObject->getCocosNode()->addChild(draw);

  this->scheduleUpdate();
  return true;
}


void GameScene::update(float deltaTime)
{
  //Update or delete objects from pool
  for (auto p = objectsPool_.begin(); p != objectsPool_.end(); p++) {

    if ((*p)->isReadyToDie) {
      p = objectsPool_.erase(p); // remove object from pool

      bool pIsEndIterator = (p == objectsPool_.end());
      if (pIsEndIterator) break;
    }
    else {
      (*p)->update(deltaTime);
    }
  }

  //Perfom Fixed Update for physic events
  fixedTimeCounter += deltaTime;
  float fixedUpdatePeriod = 1.0f / Globals::framesPerSecondFixedUpdate;
  while (fixedTimeCounter > fixedUpdatePeriod ) {
    fixedUpdate(fixedUpdatePeriod);
    fixedTimeCounter -= fixedUpdatePeriod;
  }
}


void GameScene::fixedUpdate(float deltaTime)
{
  for (auto object : objectsPool_) {
    object->fixedUpdate(deltaTime);
  }

}



