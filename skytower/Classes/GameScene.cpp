
#include "GameScene.h"
#include "Globals.h"
#include "Enums.h"
#include "Spawner.h"
#include "Rope.h"
#include "Building.h"
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

  screenSize_ = Director::getInstance()->getWinSize();

  gameLayer_ = Node::create();
  this->addChild(gameLayer_);


  //Spawn Background
  backgroundSky_ = std::unique_ptr<GameObject>(Globals::spawner.spawn("backsky"));
  backgroundSky_->getGraphic()->setParentNode(this, BACKGROUND);

  backgroundEarth_ = std::unique_ptr<GameObject>(Globals::spawner.spawn("backearth"));
  backgroundEarth_->getGraphic()->setParentNode(gameLayer_, BACKGROUND);

  //Create building base
  auto initialPosition(Vec2(screenSize_.width / 2, 100));
  building_ = std::make_unique<Building>(initialPosition);
  building_->setTag(BUILDING);
  //Add stand with grass to building
  gameObject = Globals::spawner.spawn("element-grass");
  gameObject->setPosition(Vec2(screenSize_.width / 2, 150));
  gameLayer_->addChild( gameObject->getCocosNode() );
  building_->addElement( std::shared_ptr<GameObject>(gameObject) );
  //objectsPool_.push_back(building_);



  //Create rope
  rope_ = std::make_shared<Rope>();
  auto draw = DrawNode::create();
  draw->drawSegment(Vec2(0, 0), Vec2(0, 200), 4.0f, Color4F::RED);
  draw->setContentSize(Size(4, 200));
  draw->setAnchorPoint(Vec2(0.5f, 1.0f));
  this->addChild(draw);
  rope_ = std::make_shared<Rope>();
  auto graphic = new GraphicComponent(draw);
  rope_->setGraphic(graphic);
  rope_->setTag(ROPE);
  rope_->setPosition(Vec2(screenSize_.width / 2, screenSize_.height + 20.0f));
  rope_->setRotation(30.0f);
  //add childBoject - hat (hook)
  gameObject = Globals::spawner.spawn("element-hat");
  rope_->setChild(gameObject);

  //create rotate action
  auto rotate = EaseInOut::create(RotateBy::create(3.0f, -60.0f), 2.0f);
  auto rotateRev = EaseInOut::create(RotateBy::create(3.0f, 60.0f), 2.0f);
  auto sequence = Sequence::create(rotate, rotateRev, nullptr);
  auto rotating = RepeatForever::create(sequence);
  auto move = MoveBy::create(2.0f, Vec2(0.0f, 20.0f));
  auto moveSequence = Sequence::create(move, move->reverse(), nullptr);
  auto moving = RepeatForever::create(moveSequence);
  rope_->getCocosNode()->runAction(rotating);
  rope_->getCocosNode()->runAction(moving);

  





  //gameObject = Globals::spawner.spawn("element-balcon-Blue");
  //gameObject->setPosition( Vec2(screenSize_.width / 2, screenSize_.height) );
  //gameObject->setRotation(40.0f);
  //gameLayer_->addChild( gameObject->getCocosNode() );
  //objectsPool_.push_back(std::shared_ptr<GameObject>(gameObject));

  


  auto touchListener = EventListenerMouse::create();
  touchListener->onMouseUp = CC_CALLBACK_1(GameScene::onMouseDown, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

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
  //Update view positon
  updateView();

  //Check collisons
  std::shared_ptr<GameObject> topElement = building_->getTopElement();

  for (auto object : objectsPool_) {
    object->fixedUpdate(deltaTime);

    bool objectIsFreeElement = (object->getTag() == ELEMENT_FREE);
    if (objectIsFreeElement) {

      bool intesectBuildingAndElement = topElement->getCollider()->intersectsCollider(object->getCollider());
      if (intesectBuildingAndElement) {
        object->stopMovement();
        building_->addElement(object);

        //// Add squash action
        auto scale = ScaleBy::create(0.1f, 1.2f, 0.8f);
        auto down = EaseOut::create(scale, 2.0f);
        auto up = EaseIn::create(scale->reverse(), 1.5f);
        auto action = Sequence::create(down, up, nullptr);
        object->getCocosNode()->runAction(action);
        ////
      }
    }

  }

}

void GameScene::updateView()
{
  auto elementPosition = building_->getTopElement()->getPosition();

  if ((elementPosition.y + gameLayerPos_.y) > (screenSize_.height / 3)) {
    gameLayerPos_.y -= 5;
    gameLayer_->setPosition(gameLayerPos_);
  }

}

void GameScene::onMouseDown(cocos2d::Event * event)
{
  auto gameObject = Globals::spawner.spawn("element-balcon-Blue");

  auto position = Vec2(screenSize_.width / 2 + Globals::random(-100, 100), screenSize_.height);
  gameObject->setPosition(gameLayer_->convertToNodeSpace(position));

  gameLayer_->addChild(gameObject->getCocosNode());
  objectsPool_.push_back(std::shared_ptr<GameObject>(gameObject));
}



